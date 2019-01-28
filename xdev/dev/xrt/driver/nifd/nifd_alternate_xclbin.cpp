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
#include "xclhal2.h"

INITIALIZE_EASYLOGGINGPP

using std::runtime_error;
using std::string;

void load_nifd_demo_xclbin(string xclbin_filename) {
    auto xilinx_platforms = retrieve_platform_by_name("Xilinx");
    if (xilinx_platforms.empty()) {
        LOG(WARNING) << "No Xilinx platform found";
        throw runtime_error("no xilinx platform found");
    }
    auto devices = retrieve_device_by_name(xilinx_platforms[0], "xilinx_u200_xdma_201830_2");
    if (devices.empty()) {
        LOG(WARNING) << "No valid device found";
        throw runtime_error("no valid device found");
    }
    auto device = devices[0];
    auto context = cl::Context(device);
    cl::CommandQueue q(context, device, CL_QUEUE_PROFILING_ENABLE);
    LOG(INFO) << "Loading XCLBIN from " << xclbin_filename << " ...";
    cl::Program demo_program = load_xclbin_create_program(context, {device}, xclbin_filename);
    LOG(INFO) << "XCLBIN from " << xclbin_filename << " loaded";
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

void reset_icap_with_hal() {
    LOG(INFO) << "Trying to reset ICAP through XRT HAL ...";
    int device_cnt = xclProbe();
    LOG(INFO) << "Found " << device_cnt << " devices available";
    if (device_cnt <= 0) {
        LOG(ERROR) << "No device found";
        throw runtime_error("no device found");
    }
    int device_index = 0;
    LOG(INFO) << "Opening device [" << device_cnt << "]...";
    xclDeviceHandle device_handle = xclOpen(device_index, "nifd_alternate_xclbin_reset_icap.log", xclVerbosityLevel::XCL_INFO);
    LOG(INFO) << "Device [" << device_cnt << "] opened";
    unsigned int reg_target_value = 0x4;
    unsigned long icap_offset = 0x2010c;
    LOG(INFO) << "Writing value 0x" << std::hex << reg_target_value << " to ICAP address 0x" << icap_offset << std::dec << " ...";
    int err = xclUnmgdPwrite(device_handle, 0, (void*)(&reg_target_value), sizeof(unsigned int), icap_offset);
    LOG(INFO) << "Writing to ICAP finished with return code: " << err;
    if (err < 0) {
        LOG(ERROR) << "Unmanaged write to ICAP reset failed";
        throw runtime_error("reset ICAP failed");
    }
    return;
}

void reset_card_with_hal() {
    LOG(INFO) << "Trying to reset ICAP through XRT HAL ...";
    int device_cnt = xclProbe();
    LOG(INFO) << "Found " << device_cnt << " devices available";
    if (device_cnt <= 0) {
        LOG(ERROR) << "No device found";
        throw runtime_error("no device found");
    }
    int device_index = 0;
    LOG(INFO) << "Opening device [" << device_cnt << "]...";
    xclDeviceHandle device_handle = xclOpen(device_index, "nifd_alternate_xclbin_reset_icap.log", xclVerbosityLevel::XCL_INFO);
    LOG(INFO) << "Device [" << device_cnt << "] opened";
    LOG(INFO) << "Resetting card ...";
    int err = xclResetDevice(device_handle, XCL_RESET_FULL);
    LOG(INFO) << "Resetting card finished with return code: " << err;
    return;
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
    ioctl(nifd_driver_fd, NIFD_SWITCH_ICAP_TO_NIFD, 0);
    int err = ioctl(nifd_driver_fd, NIFD_READBACK_VARIABLE, packet);
    ioctl(nifd_driver_fd, NIFD_SWITCH_ICAP_TO_PR, 0);
    LOG(INFO) << "NIFD variable read back returned with error code: " << err << ", result: " << packet[3];
    LOG(INFO) << "NIFD operations finished";
    reset_icap_with_hal();
    return;
}

void load_hello_xclbin() {
    auto xilinx_platforms = retrieve_platform_by_name("Xilinx");
    if (xilinx_platforms.empty()) {
        LOG(WARNING) << "No Xilinx platform found";
        throw runtime_error("no xilinx platform found");
    }
    auto devices = retrieve_device_by_name(xilinx_platforms[0], "xilinx_u200_xdma_201830_2");
    if (devices.empty()) {
        LOG(WARNING) << "No valid device found";
        throw runtime_error("no valid device found");
    }
    auto device = devices[0];
    auto context = cl::Context(device);
    cl::CommandQueue q(context, device, CL_QUEUE_PROFILING_ENABLE);
    string hello_filename = "/home/xsjbrd6/Desktop/darkside/farm/alveo_u200_nifd_experimental/hello/hello_kernel_hw_all.xclbin";
    LOG(INFO) << "Loading XCLBIN from " << hello_filename << " ...";
    cl::Program hello_program = load_xclbin_create_program(context, {device}, hello_filename);
    LOG(INFO) << "XCLBIN from " << hello_filename << " loaded";
    nifd_operation();
}

int nifd_alternate_xclbin(int argc, char* argv[]) {
    load_hello_xclbin();
    load_vadd_xclbin();
    return 0;
}

int main(int argc, char* argv[]) {
    START_EASYLOGGINGPP(argc, argv);
    check_logging_status();
    LOG(INFO) << "Starting nifd_alternate_xclbin ...";
    return nifd_alternate_xclbin(argc, argv);
}