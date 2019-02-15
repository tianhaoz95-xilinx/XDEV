/** @file */

// Copyright 2019 Tianhao Zhou

#include "xclhal2.h"
#include "easylogging++.h"
#include <iostream>

INITIALIZE_EASYLOGGINGPP

using namespace std;

int hal_level_callback_walkthrough(int argc, char* argv[]) {
    LOG(INFO) << "Starting hal level callback walkthough example ...";
    LOG(INFO) << "Probe about to start";
    int device_count = xclProbe();
    LOG(INFO) << "Probe finished";
    LOG(INFO) << "Found " << device_count << " devices";
    int device_index = 0;
    LOG(INFO) << "Opening device[" << device_index << "] ...";
    xclDeviceHandle device_handle = xclOpen(device_index, "open_devices_demo.log", xclVerbosityLevel::XCL_INFO);
    LOG(INFO) << "Device[" << device_index << "] opened" ;
    LOG(INFO) << "Switching on the hal level profiling plugins";
    int switch_profile_ret = xclSwitchProfiling(device_handle);
    LOG(INFO) << "xclSwitchProfiling returned with code: " << switch_profile_ret;
    LOG(INFO) << "Allocating BO onto the device ...";
    int bo_handle = xclAllocBO(device_handle, 256, xclBOKind::XCL_BO_DEVICE_RAM, -1);
    LOG(INFO) << "xclAllocBO returned with code: " << bo_handle;
    xclClose(device_handle);
    return 0;
}

int main(int argc, char* argv[]) {
    START_EASYLOGGINGPP(argc, argv);
    return hal_level_callback_walkthrough(argc, argv);
}
