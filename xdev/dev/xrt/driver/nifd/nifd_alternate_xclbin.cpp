#include <iostream>
#include "easylogging++.h"
#include "xrt/opencl/retrieve_platform.hpp"
#include "xrt/opencl/retrieve_device.hpp"
#include "xrt/opencl/load_xclbin.hpp"

INITIALIZE_EASYLOGGINGPP

int nifd_alternate_xclbin(int argc, char* argv[]) {
    auto xilinx_platforms = retrieve_platform_by_name("Xilinx");
    if (xilinx_platforms.empty()) {
        return 0;
    }
    auto devices = retrieve_device_by_name(xilinx_platforms[0], "xilinx_u200_xdma_201830_2");
    auto device = devices[0];
    auto context = cl::Context(device);
    cl::CommandQueue q(context, device, CL_QUEUE_PROFILING_ENABLE);
    string vadd_filename = "~/Desktop/darkside/alveo_u200_nifd_experimental/vadd/vadd_kernel_hw_all.xclbin";
    string hello_filename = "~/Desktop/darkside/alveo_u200_nifd_experimental/hello/hello_kernel_hw_all.xclbin";
    LOG(INFO) << "Loading XCLBIN from " << vadd_filename << " ...";
    cl::Program program = load_xclbin_create_program(context, {device}, vadd_filename);
    LOG(INFO) << "XCLBIN from " << vadd_filename << " loaded";
    // read back from NIFD
    // cl::Program program = load_xclbin_create_program(context, {device}, hello_filename);
    // check for card hang
    return 0;
}

int main(int argc, char* argv[]) {
    START_EASYLOGGINGPP(argc, argv);
    LOG(INFO) << "Starting nifd_alternate_xclbin ...";
    return nifd_alternate_xclbin(argc, argv);
}