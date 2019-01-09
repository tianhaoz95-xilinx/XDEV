/** @file */

#include "xclhal2.h"
#include "xclperf.h"
#include "xclbin.h"
// #include "read_sysfs_helper.hpp"
#include "xrt/hal/sysfs/read_sysfs.hpp"
// #include "visualize_debug_ip_layout_helper.hpp"
#include "xrt/hal/visualization/debug_ip_layout.hpp"
#include "easylogging++.h"
// #include "xclbin_helper.hpp"
#include <iostream>

#include "xrt/hal/load_xclbin.hpp"

INITIALIZE_EASYLOGGINGPP

using namespace std;

/**
 * \ingroup hal_api_demo
 * Example to use sysfs query API from xclhal2.h
 * 
 * Steps in this code:
 *  -# probe device
 *  -# open device
 *  -# load xclbin
 *  -# read debug_ip_layout using hal sysfs api
 *  -# log debug_ip_layout
 */
int sysfs_demo(int argc, char* argv[]) {
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
    // load_xclbin_with_hal_api("alveo_u200_2018_3_1/hello/hello_kernel_hw_all.xclbin", device_handle);
    load_xclbin("alveo_u200_2018_3_1/hello/hello_kernel_hw_all.xclbin", device_handle);
    LOG(INFO) << "xclbin loaded";
    char data[MAX_DEBUG_IP_LAYOUT_SIZE];
    LOG(INFO) << "Querying device[0] sysfs ...";
    LOG(INFO) << "Querying device[0] sysfs with fixed size ...";
    read_sysfs_with_config(device_handle, "icap", "debug_ip_layout", MAX_DEBUG_IP_LAYOUT_SIZE, (void*)&data[0]);
    LOG(INFO) << "Visualizing query result for Debug IP Layout ...";
    visualize_debug_ip_layout((void*)&data[0]);
    LOG(INFO) << "Querying device[0] sysfs with auto size detection ...";
    read_sysfs_with_config(device_handle, "icap", "debug_ip_layout", 0, (void*)&data[0]);
    LOG(INFO) << "Visualizing query result for Debug IP Layout ...";
    visualize_debug_ip_layout((void*)&data[0]);
    LOG(INFO) << "Closing device[0] ...";
    xclClose(device_handle);
    LOG(INFO) << "device[0] closed";
#ifdef DEMO
    LOG(INFO) << "DEMO found";
#endif
    return 0;
}

int main(int argc, char* argv[]) {
    return sysfs_demo(argc, argv);
}