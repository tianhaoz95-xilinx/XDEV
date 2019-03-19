#include <iostream>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include "easylogging++.h"
#include "project/logging.hpp"
#include "project/config.hpp"
#include "xrt/hal/sysfs/read_sysfs.hpp"
#include "xrt/opencl/retrieve_platform.hpp"
#include "xrt/opencl/retrieve_device.hpp"
#include "xrt/opencl/load_xclbin.hpp"
#include "xrt/driver/nifd/specification.hpp"
#include "xrt/driver/nifd/location.hpp"
#include "xclhal2.h"
#include "xclbin.h"

INITIALIZE_EASYLOGGINGPP

using std::runtime_error;
using std::string;
using std::cin;
using std::cout;
using std::endl;

void set_kernel_debug_bit(unsigned target_value) {
    int err = 0;
    xclDeviceHandle device_handle = xclOpen(0, "nifd_alternate_xclbin_set_debug_bit.log", xclVerbosityLevel::XCL_INFO);
    char data[MAX_IP_LAYOUT_SIZE];
    read_sysfs_with_config(device_handle, "icap", "ip_layout", MAX_IP_LAYOUT_SIZE, (void*)data);
    LOG(INFO) << "Casting raw data to ip layout";
    ip_layout* raw_layout = reinterpret_cast<ip_layout*>(data);
    LOG(INFO) << "Casting finished";
    vector<ip_data> layout;
    LOG(INFO) << "Converting ip_layout to C++ format ...";
    for (int i = 0; i < raw_layout->m_count; ++i) {
        layout.push_back(raw_layout->m_ip_data[i]);
    }
    LOG(INFO) << "Converting ip_layout to C++ format finished";
    for (auto ip : layout) {
        if (ip.m_type == IP_TYPE::IP_KERNEL) {
            uint64_t kernel_base_address = ip.m_base_address;
            uint64_t kernel_offset = 0x0;
            uint64_t absolute_offset = kernel_base_address + kernel_offset;
            unsigned write_buf[256] = {0};
            write_buf[0] = target_value;
            size_t target_size = 4;
            LOG(INFO) << "Writing debug bit to the kernel ...";
            err = xclWrite(device_handle, xclAddressSpace::XCL_ADDR_KERNEL_CTRL, absolute_offset, write_buf, target_size);
            LOG(INFO) << "Writing debug bit to the kernel finished";
            if (err < 0) {
                LOG(INFO) << "xclWrite failed with error code: " << err;
            } else {
                LOG(INFO) << "xclWrite to kernel success";
            }
        }
    }
}

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
    string vadd_filename;
    cout << "Path to the alternating xclbin: ";
    cin >> vadd_filename;
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

void reset_icap_with_ioctl() {
    string management_driver_path = get_management_driver_path();
    LOG(INFO) << "Opening management driver from " << management_driver_path << "...";
    int management_driver_fd = open(management_driver_path.c_str(), O_RDWR);
    LOG(INFO) << "Management driver from " << management_driver_path << " opened with file descriptor: " << management_driver_fd;
    LOG(INFO) << "Sending NIFD reset to management driver ...";
    int err = ioctl(management_driver_fd, XCLMGMT_RESET_NIFD);
    LOG(INFO) << "NIFD reset returned with error code: " << err;
    if (err < 0) {
        LOG(ERROR) << "ioctl to ICAP reset failed";
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
    set_kernel_debug_bit(0x100);
    LOG(INFO) << "Executing NIFD operations ...";
    string nifd_driver_path;
    cout << "Path to the NIFD driver device: ";
    cin >> nifd_driver_path;
    LOG(INFO) << "Opening NIFD driver from " << nifd_driver_path << "...";
    int nifd_driver_fd = open(nifd_driver_path.c_str(), O_RDWR);
    LOG(INFO) << "NIFD driver from " << nifd_driver_path << " opened with file descriptor: " << nifd_driver_fd;
    int err = 0;
    LOG(INFO) << "Sending signal to switch ICAP to NIFD ...";
    err = ioctl(nifd_driver_fd, NIFD_SWITCH_ICAP_TO_NIFD, 0);
    LOG(INFO) << "Switching ICAP to NIFD returned with code: " << err;
    LOG(INFO) << "Stopping the clock ...";
    err = ioctl(nifd_driver_fd, NIFD_STOP_CONTROLLED_CLOCK, 0);
    LOG(INFO) << "Stopping the clock returned with code: " << err;
    string readback_option;
    std::cout << "Continue to perform variable readback from NIFD? [y/n]: ";
    std::cin >> readback_option;
    if (readback_option == "y") {
        unsigned int packet[4];
        packet[0] = 1;
        packet[1] = 0x0000730c;
        packet[2] = 0x7ea;
        packet[3] = 0;
        LOG(INFO) << "Sending variable read back to NIFD driver ...";
        err = ioctl(nifd_driver_fd, NIFD_READBACK_VARIABLE, packet);
        LOG(INFO) << "NIFD variable read back returned with error code: " << err << ", result: " << packet[3];
    }
    LOG(INFO) << "Sending signal to switch ICAP to PR ...";
    LOG(INFO) << "Switch NIFD clock to free running mode ...";
    unsigned int mode = NIFD_FREE_RUNNING_MODE;
    err = ioctl(nifd_driver_fd, NIFD_START_CONTROLLED_CLOCK, &mode);
    LOG(INFO) << "Switch NIFD clock to free running mode returned with code: " << err;
    set_kernel_debug_bit(0x000);
    err = ioctl(nifd_driver_fd, NIFD_SWITCH_ICAP_TO_PR, 0);
    LOG(INFO) << "Switching ICAP to PR returned with code: " << err;
    LOG(INFO) << "NIFD operations finished";
    // reset_icap_with_hal();
    // reset_card_with_hal();
    // reset_icap_with_ioctl();
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
    string hello_filename;
    cout << "Path to the xclbin that runs the NIFD operations: ";
    cin >> hello_filename;
    LOG(INFO) << "Loading XCLBIN from " << hello_filename << " ...";
    cl::Program hello_program = load_xclbin_create_program(context, {device}, hello_filename);
    LOG(INFO) << "XCLBIN from " << hello_filename << " loaded";
}

int nifd_alternate_xclbin(int argc, char* argv[]) {
    load_hello_xclbin();
    nifd_operation();
    string continue_option;
    std::cout << "Continue to load vadd kernel? [y/n]: ";
    std::cin >> continue_option;
    if (continue_option == "y") {
        load_vadd_xclbin();
    }
    return 0;
}

int main(int argc, char* argv[]) {
    START_EASYLOGGINGPP(argc, argv);
    check_logging_status();
    LOG(INFO) << "Starting nifd_alternate_xclbin ...";
    return nifd_alternate_xclbin(argc, argv);
}
