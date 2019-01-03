/** @file */

#include "xclhal2.h"
#include "xclperf.h"
#include "xclbin.h"
#include "read_sysfs_helper.hpp"
#include "visualize_debug_ip_layout_helper.hpp"
#include "easylogging++.h"
#include "hal/xclbin_helper.hpp"
#include <iostream>

INITIALIZE_EASYLOGGINGPP

using namespace std;

/**
 * Example to use sysfs query API from xclhal2.h
 * 
 * Steps in this code:
 *  -# probe device
 *  -# open device
 *  -# load xclbin
 *  -# read debug_ip_layout using hal sysfs api
 *  -# log debug_ip_layout
 */
int main(int argc, char* argv[]) {
    /**
     * \b START_EASYLOGGINGPP is the entry point to easyloggingpp
     * which only needs to be called once before any logging
     */
    START_EASYLOGGINGPP(argc, argv);
    LOG(INFO) << "Starting Sysfs HAL API example ...";
    int device_count = xclProbe();
    LOG(INFO) << "Found " << device_count << " devices";
    if (device_count == 0) {
        LOG(ERROR) << "No device found";
        return -1;
    }
    LOG(INFO) << "Opening device[0] ...";
    unsigned device_index = 0;
    xclDeviceHandle device_handle = xclOpen(device_index, "sysfs_example.log", xclVerbosityLevel::XCL_INFO);
    LOG(INFO) << "device[0] opened";
    LOG(INFO) << "Loading xclbin ...";
    load_xclbin_with_hal_api("alveo_u200_2018_3_1/hello/hello_kernel_hw_all.xclbin", device_handle);
    LOG(INFO) << "xclbin loaded";
    char data[MAX_DEBUG_IP_LAYOUT_SIZE];
    LOG(INFO) << "Querying device[0] sysfs ...";
    LOG(INFO) << "Querying device[0] sysfs with fixed size ...";
    read_sysfs_with_config(device_handle, false, "", "debug_ip_layout", MAX_DEBUG_IP_LAYOUT_SIZE, (void*)&data[0]);
    LOG(INFO) << "Visualizing query result for Debug IP Layout ...";
    visualize_debug_ip_layout((void*)&data[0]);
    LOG(INFO) << "Querying device[0] sysfs with auto size detection ...";
    read_sysfs_with_config(device_handle, true, "", "debug_ip_layout", 0, (void*)&data[0]);
    LOG(INFO) << "Visualizing query result for Debug IP Layout ...";
    visualize_debug_ip_layout((void*)&data[0]);
    LOG(INFO) << "Querying device[0] sysfs with auto size detection and size as non-zero (should throw an error) ...";
    bool expected_exception_caught = false;
    try {
        read_sysfs_with_config(device_handle, true, "", "debug_ip_layout", 10, (void*)&data[0]);
    } catch (const runtime_error& e) {
        string expected_error_msg = "Read sysfs failed";
        if (string(e.what()) == expected_error_msg) {
            LOG(INFO) << "Expected failure with error message: " << e.what();
            expected_exception_caught = true;
        } else {
            LOG(INFO) << "Unexpected failure with error message: " << e.what() << ", expecting " << expected_error_msg;
        }
    }
    if (!expected_exception_caught) {
        LOG(INFO) << "Query with read_all and size as non-zero should throw an exception, but non seen";
        throw runtime_error("Expected exception not seen");
    }
    LOG(INFO) << "Closing device[0] ...";
    xclClose(device_handle);
    LOG(INFO) << "device[0] closed";
    return 0;
}