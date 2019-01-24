#include <iostream>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include "easylogging++.h"
#include "project/logging.hpp"
#include "xrt/opencl/retrieve_platform.hpp"
#include "xrt/opencl/retrieve_device.hpp"
#include "xrt/opencl/load_xclbin.hpp"
#include "xrt/driver/nifd/specification.hpp"
#include "xrt/driver/nifd/location.hpp"

INITIALIZE_EASYLOGGINGPP

void load_hello_xclbin() {
    auto xilinx_platforms = retrieve_platform_by_name("Xilinx");
    if (xilinx_platforms.empty()) {
        LOG(WARNING) << "No Xilinx platform found";
        return;
    }
    auto devices = retrieve_device_by_name(xilinx_platforms[0], "xilinx_u200_xdma_201830_2");
    if (devices.empty()) {
        LOG(WARNING) << "No valid device found";
        return;
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
        return;
    }
    auto devices = retrieve_device_by_name(xilinx_platforms[0], "xilinx_u200_xdma_201830_2");
    if (devices.empty()) {
        LOG(WARNING) << "No valid device found";
        return;
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
    LOG(INFO) << "Executing NIFD operations ...";
    string nifd_driver_path = get_nifd_driver_path();
    LOG(INFO) << "Opening NIFD driver from " << nifd_driver_path << "...";
    int nifd_driver_fd = open(nifd_driver_path.c_str(), O_RDWR);
    LOG(INFO) << "NIFD driver from " << nifd_driver_path << " opened with file descriptor: " << nifd_driver_fd;
    unsigned int packet[4];
    packet[0] = 1;
    packet[1] = 0;
    packet[2] = 0;
    packet[3] = 0;
    LOG(INFO) << "Sending variable read back to NIFD driver ...";
    int err = ioctl(nifd_driver_fd, NIFD_READBACK_VARIABLE, packet);
    LOG(INFO) << "NIFD variable read back returned with error code: " << err << ", result: " << packet[3];
    LOG(INFO) << "NIFD operations finished";
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