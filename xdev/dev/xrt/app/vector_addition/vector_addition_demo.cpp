/** @file */

#include <iostream>
#include "easylogging++.h"
#include "xrt/opencl/retrieve_platform.hpp"
#include "xrt/opencl/retrieve_device.hpp"
#include "xrt/opencl/load_xclbin.hpp"

INITIALIZE_EASYLOGGINGPP

int vector_addition_demo(int argc, char* argv[]) {
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
}

int main(int argc, char* argv[]) {
    START_EASYLOGGINGPP(argc, argv);
    return vector_addition_demo(argc, argv);
}