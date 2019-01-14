/** @file */

// Copyright 2019 Tianhao Zhou

#include "xclhal2.h"
#include "easylogging++.h"
#include <iostream>

INITIALIZE_EASYLOGGINGPP

using namespace std;

/**
 * Example for opening devices
 */
int open_devices_demo(int argc, char* argv[]) {
    START_EASYLOGGINGPP(argc, argv);
    LOG(INFO) << "Starting Probe example ...";
    LOG(INFO) << "Probe about to start";
    int device_count = xclProbe();
    LOG(INFO) << "Probe finished";
    LOG(TRACE) << "Found " << device_count << " devices";
    int device_index = 0;
    LOG(INFO) << "Opening device[" << device_index << "] ...";
    xclDeviceHandle device_handle = xclOpen(device_index, "open_devices_demo.log", xclVerbosityLevel::XCL_INFO);
    LOG(INFO) << "Device[" << device_index << "] opened" ;

    LOG(INFO) << "Closing device[0] ...";
    xclClose(device_handle);
    LOG(INFO) << "device[0] closed";
    return 0;
}

int main(int argc, char* argv[]) {
    return open_devices_demo(argc, argv);
}

