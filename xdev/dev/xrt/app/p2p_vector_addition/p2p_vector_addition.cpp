/** @file */

#include <iostream>
#include "easylogging++.h"
#include "xrt/opencl/retrieve_platform.hpp"
#include "xrt/opencl/retrieve_device.hpp"
#include "xrt/opencl/load_xclbin.hpp"

INITIALIZE_EASYLOGGINGPP

int p2p_vector_addition(int argc, char* argv[]) {
    std::vector<cl::Platform> platforms = retrieve_platform_by_name("Xilinx");
    cl::Platform platform = platforms[0];
    std::vector<cl::Device> devices;
    vector<cl::Device> u200_devices = retrieve_device_by_name(platform, "xilinx_u200_xdma_201830_1");
    if (u200_devices.empty()) {
        return -1;
    }
    cl::Device u200_device = u200_devices[0];
    vector<cl::Device> vcu1525_devices = retrieve_device_by_name(platform, "xilinx_vcu1525_xdma_201830_1");
    if (vcu1525_devices.size() == 0) {
        return -1;
    }
    cl::Device vcu1525_device = vcu1525_devices[0];
    return 0;
}

int main(int argc, char* argv[]) {
    START_EASYLOGGINGPP(argc, argv);
    return p2p_vector_addition(argc, argv);
}