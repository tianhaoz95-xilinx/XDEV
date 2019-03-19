/** @file */

#include <iostream>
#include "easylogging++.h"
#include "xrt/opencl/retrieve_platform.hpp"
#include "xrt/opencl/retrieve_device.hpp"
#include "xrt/opencl/load_xclbin.hpp"

INITIALIZE_EASYLOGGINGPP

using std::cout;
using std::cin;
using std::endl;

int vector_addition_demo(int argc, char* argv[]) {
    /*
    auto xilinx_platforms = retrieve_platform_by_name("Xilinx");
    if (xilinx_platforms.empty()) {
        return 0;
    }
    auto devices = retrieve_device_by_name(xilinx_platforms[0], "xilinx_u200_xdma_201830_1");
    if (devices.empty()) {
        return 0;
    }
    auto device = devices[0];
    auto context = cl::Context(device);
    cl::CommandQueue q(context, device, CL_QUEUE_PROFILING_ENABLE);
    return 0;
    */

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
    string xclbinFilename;
    cout << "The vadd xclbin to be loaded: ";
    cin >> xclbinFilename;
    LOG(INFO) << "Loading: '" << xclbinFilename << " ...";
    std::ifstream bin_file(xclbinFilename, std::ifstream::binary);
    bin_file.seekg (0, bin_file.end);
    unsigned nb = bin_file.tellg();
    bin_file.seekg (0, bin_file.beg);
    char *buf = new char[nb];
    bin_file.read(buf, nb);
    cl::Program::Binaries bins;
    bins.push_back({buf,nb});
    devices.resize(1);
    cl::Program program(context, devices, bins);
    LOG(INFO) << "OpenCL program created";
    string kernel_name;
    cout << "The vadd kernel name to be loaded [vadd_kernel for XDEV and krnl_vadd for Xilinx examples]: ";
    cin >> kernel_name;
    cl::Kernel krnl_vector_add(program, kernel_name);
    LOG(INFO) << "Vector addition kernel created";
    cl::Buffer buffer_a(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_ONLY, size_in_bytes, source_a.data());
    LOG(INFO) << "Buffer A created";
    cl::Buffer buffer_b(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_ONLY, size_in_bytes, source_b.data());
    LOG(INFO) << "Buffer B created";
    cl::Buffer buffer_result(context, CL_MEM_USE_HOST_PTR | CL_MEM_WRITE_ONLY, size_in_bytes, source_results.data());
    LOG(INFO) << "Buffer Result created";
    q.enqueueMigrateMemObjects({buffer_a,buffer_b},0);
    LOG(INFO) << "Buffer A and B migration enqueued";
    int narg=0;
    krnl_vector_add.setArg(narg++,buffer_a);
    krnl_vector_add.setArg(narg++,buffer_b);
    krnl_vector_add.setArg(narg++,buffer_result);
    krnl_vector_add.setArg(narg++,DATA_SIZE);
    q.enqueueTask(krnl_vector_add);
    LOG(INFO) << "Vector addition enqueued";
    q.enqueueMigrateMemObjects({buffer_result, buffer_result, buffer_result, buffer_result},CL_MIGRATE_MEM_OBJECT_HOST);
    LOG(INFO) << "Buffer Result migration enqueued";
    q.finish();
    LOG(INFO) << "Command queue cleared";
    int match = 0;
    for (int i = 0; i < DATA_SIZE; i++) {
        int host_result = source_a[i] + source_b[i];
        if (source_results[i] != host_result) {
            match = 1;
            break;
        }
    }
    LOG(INFO) << "TEST " << (match ? "FAILED" : "PASSED");
    return match;
}

int main(int argc, char* argv[]) {
    START_EASYLOGGINGPP(argc, argv);
    return vector_addition_demo(argc, argv);
}