#include <iostream>
#include "easylogging++.h"
#include "project/logging.hpp"
#include "xrt/opencl/retrieve_platform.hpp"
#include "xrt/opencl/retrieve_device.hpp"
#include "xrt/opencl/load_xclbin.hpp"

INITIALIZE_EASYLOGGINGPP

void load_hello_xclbin() {
    auto xilinx_platforms = retrieve_platform_by_name("Xilinx");
    if (xilinx_platforms.empty()) {
        LOG(WARNING) << "No Xilinx platform found";
        return 0;
    }
    auto devices = retrieve_device_by_name(xilinx_platforms[0], "xilinx_u200_xdma_201830_2");
    if (devices.empty()) {
        LOG(WARNING) << "No valid device found";
        return 0;
    }
    auto device = devices[0];
    auto context = cl::Context(device);
    cl::CommandQueue q(context, device, CL_QUEUE_PROFILING_ENABLE);
    string hello_filename = "/home/xsjbrd6/Desktop/darkside/farm/alveo_u200_nifd_experimental/hello/hello_kernel_hw_all.xclbin";
    LOG(INFO) << "Loading XCLBIN from " << hello_filename << " ...";
    cl::Program hello_program = load_xclbin_create_program(context, {device}, hello_filename);
    LOG(INFO) << "XCLBIN from " << hello_filename << " loaded";
}

void load_vadd_xclbin() {
    auto xilinx_platforms = retrieve_platform_by_name("Xilinx");
    if (xilinx_platforms.empty()) {
        LOG(WARNING) << "No Xilinx platform found";
        return 0;
    }
    auto devices = retrieve_device_by_name(xilinx_platforms[0], "xilinx_u200_xdma_201830_2");
    if (devices.empty()) {
        LOG(WARNING) << "No valid device found";
        return 0;
    }
    auto device = devices[0];
    auto context = cl::Context(device);
    cl::CommandQueue q(context, device, CL_QUEUE_PROFILING_ENABLE);
    string vadd_filename = "/home/xsjbrd6/Desktop/darkside/farm/alveo_u200_nifd_experimental/vadd/vadd_kernel_hw_all.xclbin";
    LOG(INFO) << "Loading XCLBIN from " << vadd_filename << " ...";
    cl::Program vadd_program = load_xclbin_create_program(context, {device}, vadd_filename);
    LOG(INFO) << "XCLBIN from " << vadd_filename << " loaded";
}

void nifd_operation() {
    return;
}

int nifd_alternate_xclbin(int argc, char* argv[]) {
    load_hello_xclbin();
    nifd_operation();
    load_vadd_xclbin();
    return 0;
}

int main(int argc, char* argv[]) {
    START_EASYLOGGINGPP(argc, argv);
    check_logging_status();
    LOG(INFO) << "Starting nifd_alternate_xclbin ...";
    return nifd_alternate_xclbin(argc, argv);
}