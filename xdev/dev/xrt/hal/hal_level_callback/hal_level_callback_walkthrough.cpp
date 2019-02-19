/** @file */

// Copyright 2019 Tianhao Zhou

#include "xclhal2.h"
#include "easylogging++.h"
#include <iostream>

INITIALIZE_EASYLOGGINGPP

using namespace std;

void hal_calls(bool profile) {
    LOG(INFO) << "Starting hal level callback walkthough example ...";
    LOG(INFO) << "Probe about to start";
    int device_count = xclProbe();
    LOG(INFO) << "Probe finished";
    LOG(INFO) << "Found " << device_count << " devices";
    int device_index = 0;
    LOG(INFO) << "Opening device[" << device_index << "] ...";
    xclDeviceHandle device_handle = xclOpen(device_index, "hal_level_callback_walkthrough.log", xclVerbosityLevel::XCL_INFO);
    LOG(INFO) << "Device[" << device_index << "] opened" ;
    if (profile) {
        LOG(INFO) << "Switching on the hal level profiling plugins";
        HalPluginConfig config = {0};
        int switch_profile_ret = xclConfigPlugin(device_handle, &config);
        LOG(INFO) << "xclSwitchProfiling returned with code: " << switch_profile_ret;
    }
    LOG(INFO) << "Allocating BO a onto the device ...";
    int bo_handle_a = xclAllocBO(device_handle, 64, xclBOKind::XCL_BO_DEVICE_RAM, 1);
    LOG(INFO) << "xclAllocBO returned with code: " << bo_handle_a;
    LOG(INFO) << "Allocating BO b onto the device ...";
    int bo_handle_b = xclAllocBO(device_handle, 64, xclBOKind::XCL_BO_DEVICE_RAM, 1);
    LOG(INFO) << "xclAllocBO returned with code: " << bo_handle_b;
    LOG(INFO) << "Allocating BO c onto the device ...";
    int bo_handle_c = xclAllocBO(device_handle, 64, xclBOKind::XCL_BO_DEVICE_RAM, 1);
    LOG(INFO) << "xclAllocBO returned with code: " << bo_handle_c;
    LOG(INFO) << "Writing 0 to buffer a ...";
    char bo_a_write_buf[256] = {0};
    int write_bo_a_ret = xclWriteBO(device_handle, bo_handle_a, (void*)bo_a_write_buf, 64, 0);
    LOG(INFO) << "xclWriteBO returned with code: " << write_bo_a_ret;
    LOG(INFO) << "Reading from buffer a ...";
    char bo_a_read_buf[256] = {0};
    int read_bo_a_ret = xclReadBO(device_handle, bo_handle_a, (void*)bo_a_read_buf, 64, 0);
    LOG(INFO) << "xclReadBO returned with code: " << read_bo_a_ret;
    xclClose(device_handle);
}

int hal_level_callback_walkthrough(int argc, char* argv[]) {
    hal_calls(false);
    hal_calls(true);
    return 0;
}

int main(int argc, char* argv[]) {
    START_EASYLOGGINGPP(argc, argv);
    return hal_level_callback_walkthrough(argc, argv);
}
