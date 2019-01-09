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

INITIALIZE_EASYLOGGINGPP

using namespace std;

enum NIFDCommand {
  NIFD_ACQUIRE_CU             = 0,
  NIFD_RELEASE_CU             = 1,
  NIFD_QUERY_CU               = 2,
  NIFD_READBACK_VARIABLE      = 3,
  NIFD_SWITCH_ICAP_TO_NIFD    = 4,
  NIFD_SWITCH_ICAP_TO_PR      = 5,
  NIFD_ADD_BREAKPOINTS        = 6,
  NIFD_REMOVE_BREAKPOINTS     = 7,
  NIFD_CHECK_STATUS           = 8,
  NIFD_QUERY_XCLBIN           = 9,
  NIFD_STOP_CONTROLLED_CLOCK  = 10,
  NIFD_START_CONTROLLED_CLOCK = 11,
  NIFD_SWITCH_CLOCK_MODE      = 12
};

#define NIFD_FREE_RUNNING_MODE 1
#define NIFD_STEPPING_MODE     2

std::atomic<bool> finished(false);

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

string get_xdma_driver_path() {
    return "/dev/dri/renderD129";
}

string get_nifd_driver_path() {
    return "/dev/nifd.m";
}

string get_xclbin_path() {
    return "/proj/isi_group/isim/tianhaoz/Misc/nifd_xclbin/binary_container_with_better_debug_data.xclbin";
}

void run_kernel(int nifd_driver_fd, bool pause) {
    int DATA_SIZE = 4096;
    size_t size_in_bytes = DATA_SIZE * sizeof(int);
    std::vector<int,aligned_allocator<int>> source_a(DATA_SIZE, 10);
    std::vector<int,aligned_allocator<int>> source_b(DATA_SIZE, 32);
    std::vector<int,aligned_allocator<int>> source_results(DATA_SIZE);
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    cl::Platform platform = platforms[0];
    std::vector<cl::Device> devices;
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
    cl::Kernel krnl_vector_add(program,"krnl_vadd");
    cl::Buffer buffer_a(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_ONLY,  
            size_in_bytes, source_a.data());
    cl::Buffer buffer_b(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_ONLY,  
            size_in_bytes, source_b.data());
    cl::Buffer buffer_result(context, CL_MEM_USE_HOST_PTR | CL_MEM_WRITE_ONLY, 
            size_in_bytes, source_results.data());
    if (pause) {
        ioctl(nifd_driver_fd, NIFDCommand::NIFD_STOP_CONTROLLED_CLOCK, 0);
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
    LOG(INFO) << "TEST " << (match ? "FAILED" : "PASSED") << ", pause: ", pause;
}

int nifd_driver_demo(int argc, char* argv[]) {
    START_EASYLOGGINGPP(argc, argv);
    
    string nifd_driver_path = get_nifd_driver_path();
    string xdma_driver_path = get_xdma_driver_path();

    int nifd_driver_fd = open(nifd_driver_path.c_str(), O_RDWR);
    LOG(INFO) << "NIFD driver file descriptor return value: " << nifd_driver_fd;
    int xdma_driver_fd = open(xdma_driver_path.c_str(), O_RDWR);
    LOG(INFO) << "XDMA driver file descriptor return value: " << xdma_driver_fd;

    auto mode = NIFD_FREE_RUNNING_MODE;
    LOG(INFO) << "Turning on NIFD clock ...";
    ioctl(nifd_driver_fd, NIFD_START_CONTROLLED_CLOCK, &mode);
    LOG(INFO) << "NIFD clock is on";

    LOG(INFO) << "Running kernel without NIFD ...";
    run_kernel(nifd_driver_fd, false);
    LOG(INFO) << "Succeeded without NIFD";

    LOG(INFO) << "Running kernel with NIFD in separate thread ...";
    std::thread kernel_thread(run_kernel, nifd_driver_fd, true);
    LOG(INFO) << "Thread created";

    int wait_cnt = 5;

    for (int i = 0; i < wait_cnt; ++i) {
        if (finished) {
            LOG(INFO) << "Finished";
        } else {
            LOG(INFO) << "Not finished";
        }
        std::this_thread::sleep_for (std::chrono::seconds(1));
    }

    ioctl(nifd_driver_fd, NIFD_START_CONTROLLED_CLOCK, &mode) ;

    kernel_thread.join();

    if (finished) {
        LOG(INFO) << "Finished";
    } else {
        LOG(INFO) << "Not finished";
    }

    close(nifd_driver_fd);
    close(xdma_driver_fd);

    return 0;
}

int main(int argc, char* argv[]) {
    return nifd_driver_demo(argc, argv);
}