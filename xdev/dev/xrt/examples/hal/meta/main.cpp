/** @file */

#include "xclhal2.h"
#include "easylogging++.h"
#include <iostream>

INITIALIZE_EASYLOGGINGPP

using namespace std;

/**
 * Example for using hal meta API
 */
int main(int argc, char* argv[]) {
    /**
     * \code{.cpp}
     * START_EASYLOGGINGPP(argc, argv);
     * \endcode
     * 
     * is the entry point to easyloggingpp 
     * which only needs to be called once 
     * before any logging
     */
    START_EASYLOGGINGPP(argc, argv);
    LOG(INFO) << "Starting Probe example ...";
    LOG(INFO) << "Probe about to start";
    int device_count = xclProbe();
    LOG(INFO) << "Probe finished";
    LOG(TRACE) << "Found " << device_count << " devices";
    for (int i = 0; i < device_count; ++i) {
        LOG(INFO) << "Starting device[" << i << "]";
        string log_filename = "meta_example_device_" + to_string(i) + ".log";
        xclDeviceHandle device_handle = xclOpen(i, log_filename.c_str(), xclVerbosityLevel::XCL_INFO);

        LOG(INFO) << "Closing device[" << i << "]";
        xclClose(device_handle);
        LOG(INFO) << "Finished Closing device[" << i << "]";
    }
    return 0;
}