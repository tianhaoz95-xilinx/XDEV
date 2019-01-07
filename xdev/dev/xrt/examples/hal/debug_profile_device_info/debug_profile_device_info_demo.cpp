/**
 * @file
 * \ingroup hal_api_demo
 */

#include "xclhal2.h"
#include "xclperf.h"
#include "easylogging++.h"
#include <iostream>

INITIALIZE_EASYLOGGINGPP

using namespace std;

/**
 * \ingroup hal_api_demo
 * \section debug_profile_device_info_demo Debug & Profile Device Info API demo
 * \author Tianhao Zhou
 * \date 1/2/2019
 * \version dev
 * \subsection intro Introduction
 * This code snipet uses xclGetDebugProfileDeviceInfo
 * with minimum amount of other APIs, making it a good
 * tool for developing and debugging the API.
 * \subsection details Details
 *  -# Probe
 *  -# Open 1 device at a time
 *  -# Get debug profile device info
 *  -# Print the info
 *  -# Close device
 * \subsection future Future Plans
 * none
 */
int debug_profile_device_info_demo(int argc, char* argv[]) {
    /**
     * \note
     * \b START_EASYLOGGINGPP is the entry point 
     * to easyloggingpp which should be called 
     * only once before any logging
     */
    START_EASYLOGGINGPP(argc, argv);
    LOG(INFO) << "Starting Probe example ...";
    LOG(INFO) << "Probe about to start";
    int device_count = xclProbe();
    LOG(INFO) << "Probe finished";
    LOG(INFO) << "Found " << device_count << " devices";
    for (int i = 0; i < device_count; ++i) {
        LOG(INFO) << "Starting device[" << i << "]";
        string log_filename = "meta_example_device_" + to_string(i) + ".log";
        LOG(INFO) << "Opening device[" << i << "]";
        xclDeviceHandle device_handle = xclOpen(i, log_filename.c_str(), xclVerbosityLevel::XCL_INFO);
        LOG(INFO) << "Finished opening device[" << i << "]";
        xclDebugProfileDeviceInfo info;
        int err = xclGetDebugProfileDeviceInfo(device_handle, info);
        if (err) {
            LOG(ERROR) << "Failed to get debug and profile meta";
            throw runtime_error("Read meta failed");
        }
        unsigned int device_index = (unsigned int)info.device_index;
        unsigned int user_instance = (unsigned int)info.user_instance;
        unsigned int mgmt_instance = (unsigned int)info.mgmt_instance;
        unsigned int nifd_instance = (unsigned int)info.nifd_instance;
        unsigned int device_type = (unsigned int)info.device_type;
        string device_name = (string)info.device_name;
        string nifd_name = (string)info.nifd_name;
        LOG(INFO) << "\t Showing device[" << i << "] info:";
        LOG(INFO) << "\t\t Device Index: " << device_index;
        LOG(INFO) << "\t\t Device Type: " << device_type;
        LOG(INFO) << "\t\t User Instance: " << user_instance;
        LOG(INFO) << "\t\t NIFD Instance: " << nifd_instance;
        LOG(INFO) << "\t\t Management Instance: " << mgmt_instance;
        LOG(INFO) << "\t\t Device Name: " << device_name;
        LOG(INFO) << "\t\t NIFD Name: " << nifd_name;
        LOG(INFO) << "Closing device[" << i << "]";
        xclClose(device_handle);
        LOG(INFO) << "Finished closing device[" << i << "]";
    }
    return 0;
}

int main(int argc, char* argv[]) {
    return debug_profile_device_info_demo(argc, argv);
}