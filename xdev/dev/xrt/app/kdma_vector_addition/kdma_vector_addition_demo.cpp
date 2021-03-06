/** @file */

#include <iostream>
#include "easylogging++.h"
#include "xrt/opencl/retrieve_platform.hpp"
#include "xrt/opencl/retrieve_device.hpp"
#include "xrt/opencl/load_xclbin.hpp"

using std::string;

INITIALIZE_EASYLOGGINGPP

int kdma_vector_addition_demo(int argc, char* argv[]) {
    unsigned long xdma_spm_offset = 0x00270000;
    unsigned long p2p_spm_offset = 0x00280000;
    unsigned long kdma_spm_offset = 0x00290000;

    auto xilinx_platforms = retrieve_platform_by_name("Xilinx");
    if (xilinx_platforms.empty()) {
        LOG(INFO) << "No valid platform found";
        return 0;
    }
    auto devices = retrieve_device_by_name(xilinx_platforms[0], "xilinx_u200_xdma_201830_2");
    if (devices.empty()) {
        LOG(INFO) << "No valid device found";
        return 0;
    }
    LOG(INFO) << "Creating the device ...";
    auto device = devices[0];
    LOG(INFO) << "Device created, Creating the context ...";
    auto context = cl::Context(device);
    LOG(INFO) << "Context created. Constructing the command queue";
    cl::CommandQueue q(context, device, CL_QUEUE_PROFILING_ENABLE);
    LOG(INFO) << "The command queue constructed";
    int data_size = 256;
    std::vector<int,aligned_allocator<int>> source_a(data_size, 0);
    std::vector<int,aligned_allocator<int>> source_b(data_size, 0);
    std::vector<int,aligned_allocator<int>> source_results(data_size);
    for (int i = 0; i < data_size; ++i) {
        source_a[i] = i;
    }
    string xclbin_filename = "/home/xsjbrd6/Desktop/darkside/farm/alveo_kdma_p2p_verify/vadd/vadd_kernel_hw_all.xclbin";
    LOG(INFO) << "Loading xclbin from " << xclbin_filename << " ...";
    cl::Program program = load_xclbin_create_program(context, {device}, xclbin_filename);
    LOG(INFO) << "Constructing vadd kernel from the program ...";
    cl::Kernel krnl_vector_add(program, "vadd_kernel");
    LOG(INFO) << "The vadd kernel is constructed";
    int size_in_bytes = data_size * sizeof(int);
    cl::Buffer buffer_a(context, CL_MEM_USE_HOST_PTR|CL_MEM_READ_ONLY|CL_MEM_EXT_PTR_XILINX, size_in_bytes, source_a.data());
    cl::Buffer buffer_b(context, CL_MEM_USE_HOST_PTR|CL_MEM_READ_ONLY|CL_MEM_EXT_PTR_XILINX, size_in_bytes, source_b.data());
    cl::Buffer buffer_result(context, CL_MEM_USE_HOST_PTR|CL_MEM_WRITE_ONLY|CL_MEM_EXT_PTR_XILINX, size_in_bytes, source_results.data());
    LOG(INFO) << "Migrating buffer_a and buffer_b";
    q.enqueueMigrateMemObjects({buffer_a,buffer_b}, 0);
    LOG(INFO) << "Waiting for migration to finish";
    q.finish();
    LOG(INFO) << "Migrating buffer_a and buffer_b finished, copying buffer_a to buffer_b";
    q.enqueueCopyBuffer(buffer_a, buffer_b, 0, 0, size_in_bytes);
    LOG(INFO) << "Waiting for buffer copying to finish";
    q.finish();
    LOG(INFO) << "Buffer copying finished";
    krnl_vector_add.setArg(0, buffer_a);
    krnl_vector_add.setArg(1, buffer_b);
    krnl_vector_add.setArg(2, buffer_result);
    krnl_vector_add.setArg(3, data_size);
    LOG(INFO) << "Enqueuing vadd task";
    q.enqueueTask(krnl_vector_add);
    LOG(INFO) << "Enqueuing result buffer migration to fetch the results";
    q.enqueueMigrateMemObjects({buffer_result},CL_MIGRATE_MEM_OBJECT_HOST);
    LOG(INFO) << "Waiting for the queue to finish up";
    q.finish();
    LOG(INFO) << "All tasks finished";
    for (int i = 0; i < 5; i++) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}

int main(int argc, char* argv[]) {
    START_EASYLOGGINGPP(argc, argv);
    return kdma_vector_addition_demo(argc, argv);
}