/** @file */

#define CL_HPP_CL_1_2_DEFAULT_BUILD
#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#define CL_HPP_ENABLE_PROGRAM_CONSTRUCTION_FROM_ARRAY_COMPATIBILITY 1

#include <iostream>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <thread>
#include <CL/cl2.hpp>
#include <vector>
#include <atomic>
#include <chrono>
#include "easylogging++.h"
#include "xrt/driver/nifd/specification.hpp"
#include "xrt/driver/nifd/location.hpp"

INITIALIZE_EASYLOGGINGPP

using namespace std;

std::atomic<bool> finished(false);
std::atomic<bool> stopped(false);

//Customized buffer allocation for 4K boundary alignment
template <typename T>
struct aligned_allocator
{
  using value_type = T;
  T* allocate(std::size_t num)
  {
    void* ptr = nullptr;
    if (posix_memalign(&ptr,4096,num*sizeof(T)))
      throw std::bad_alloc();
    return reinterpret_cast<T*>(ptr);
  }
  void deallocate(T* p, std::size_t num)
  {
    free(p);
  }
};

void run_kernel(int nifd_driver_fd, bool pause) {
    if (pause) {
        LOG(INFO) << "Start pausing example ...";
    } else {
        LOG(INFO) << "Start free running example ...";
    }
    int DATA_SIZE = 4096;
    size_t size_in_bytes = DATA_SIZE * sizeof(int);
    std::vector<int,aligned_allocator<int>> source_a(DATA_SIZE, 10);
    std::vector<int,aligned_allocator<int>> source_b(DATA_SIZE, 32);
    std::vector<int,aligned_allocator<int>> source_results(DATA_SIZE);
    std::vector<cl::Platform> platforms;
    LOG(INFO) << "Getting OpenCL platforms ...";
    cl::Platform::get(&platforms);
    cl::Platform platform = platforms[0];
    std::vector<cl::Device> devices;
    LOG(INFO) << "Getting OpenCL devices ...";
    platform.getDevices(CL_DEVICE_TYPE_ACCELERATOR, &devices);
    cl::Device device = devices[0];
    cl::Context context(device);
    cl::CommandQueue q(context, device, CL_QUEUE_PROFILING_ENABLE);
    string xclbinFilename = get_xclbin_path();
    LOG(INFO) << "Loading: '" << xclbinFilename;
    std::ifstream bin_file(xclbinFilename, std::ifstream::binary);
    bin_file.seekg (0, bin_file.end);
    unsigned nb = bin_file.tellg();
    bin_file.seekg (0, bin_file.beg);
    char *buf = new char [nb];
    bin_file.read(buf, nb);
    cl::Program::Binaries bins;
    bins.push_back({buf,nb});
    devices.resize(1);
    cl::Program program(context, devices, bins);
    cl::Kernel krnl_vector_add(program,"vadd_kernel");
    cl::Buffer buffer_a(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_ONLY,  
            size_in_bytes, source_a.data());
    cl::Buffer buffer_b(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_ONLY,  
            size_in_bytes, source_b.data());
    cl::Buffer buffer_result(context, CL_MEM_USE_HOST_PTR | CL_MEM_WRITE_ONLY, 
            size_in_bytes, source_results.data());
    if (pause) {
        unsigned int mode = NIFD_FREE_RUNNING_MODE;
        int err = 0;

        LOG(INFO) << "Switching ICAP clock to NIFD ...";
        err = ioctl(nifd_driver_fd, NIFD_SWITCH_ICAP_TO_NIFD, 0);
        LOG(INFO) << "Switching ICAP clock to NIFD finished with return code: " << err;

        // LOG(INFO) << "Turning on NIFD clock ...";
        // err = ioctl(nifd_driver_fd, NIFD_START_CONTROLLED_CLOCK, &mode);
        // LOG(INFO) << "Turning on NIFD clock finished with return code: " << err;

        LOG(INFO) << "Turning off NIFD clock ...";
        err = ioctl(nifd_driver_fd, NIFD_STOP_CONTROLLED_CLOCK, 0);
        LOG(INFO) << "Turning off NIFD clock finished with return code: " << err;
        stopped = true;
    }
    q.enqueueMigrateMemObjects({buffer_a,buffer_b},0);
    int narg=0;
    krnl_vector_add.setArg(narg++,buffer_a);
    krnl_vector_add.setArg(narg++,buffer_b);
    krnl_vector_add.setArg(narg++,buffer_result);
    krnl_vector_add.setArg(narg++,DATA_SIZE);
    q.enqueueTask(krnl_vector_add);
    q.enqueueMigrateMemObjects({buffer_result, buffer_result, buffer_result, buffer_result},CL_MIGRATE_MEM_OBJECT_HOST);
    q.finish();
    if (pause) {
        finished = true;
    }
    int match = 0;
    for (int i = 0; i < DATA_SIZE; i++) {
        int host_result = source_a[i] + source_b[i];
        if (source_results[i] != host_result) {
            match = 1;
            break;
        }
    }
    LOG(INFO) << "TEST " << (match ? "FAILED" : "PASSED") << ", pause: " << pause;
}

int nifd_driver_demo(int argc, char* argv[]) {
    START_EASYLOGGINGPP(argc, argv);
    
    string nifd_driver_path = get_nifd_driver_path();
    int err = 0;

    LOG(INFO) << "Opening NIFD driver from " << nifd_driver_path << "...";
    int nifd_driver_fd = open(nifd_driver_path.c_str(), O_RDWR);
    LOG(INFO) << "NIFD driver from " << nifd_driver_path << " opened with file descriptor: " << nifd_driver_fd;

    unsigned int mode = NIFD_FREE_RUNNING_MODE;

    LOG(INFO) << "Running kernel without NIFD ...";
    run_kernel(nifd_driver_fd, false);
    LOG(INFO) << "Succeeded without NIFD";

    LOG(INFO) << "Running kernel with NIFD in separate thread ...";
    std::thread kernel_thread(run_kernel, nifd_driver_fd, true);
    LOG(INFO) << "Thread created";

    int wait_cnt = 5;

    for (int i = 0; i < wait_cnt; ++i) {
        LOG(INFO) << "Waiting for 1 second ...";
        std::this_thread::sleep_for (std::chrono::seconds(1));
        if (finished) {
            LOG(INFO) << "Finished: NIFD pausing is not working";
        } else {
            LOG(INFO) << "Not finished: normal behaviour";
        }
    }

    while (!stopped) {
        std::this_thread::sleep_for (std::chrono::seconds(1));
    }

    mode = NIFD_FREE_RUNNING_MODE;
    LOG(INFO) << "Turning on NIFD clock ...";
    err = ioctl(nifd_driver_fd, NIFD_START_CONTROLLED_CLOCK, &mode) ;
    LOG(INFO) << "Turning on NIFD clock finished with return code: " << err;

    LOG(INFO) << "Switching ICAP clock to PR ...";
    err = ioctl(nifd_driver_fd, NIFD_SWITCH_ICAP_TO_PR, 0);
    LOG(INFO) << "Switching ICAP clock to PR finished with return code: " << err;

    LOG(INFO) << "Waiting for the NIFD kernel thread to finish ...";
    kernel_thread.join();
    LOG(INFO) << "NIFD kernel thread finished";

    if (finished) {
        LOG(INFO) << "Finished: normal behaviour";
    } else {
        LOG(INFO) << "Not finished: kernel hang";
    }

    close(nifd_driver_fd);

    return 0;
}

int main(int argc, char* argv[]) {
    return nifd_driver_demo(argc, argv);
}