/** @file */

#include "xclhal2.h"
#include "xclperf.h"
#include "xclbin.h"
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
    LOG(INFO) << "Sysfs result buffer constructed ...";
    xclSysfsQuery query;
    LOG(INFO) << "Querying device[0] sysfs ...";
    query.size = MAX_DEBUG_IP_LAYOUT_SIZE;
    int err = xclReadSysfs(device_handle, query, (void*)&data[0]);
    LOG(INFO) << "Query device[0] sysfs finished ...";
    if (err) {
        LOG(ERROR) << "Casting sysfs result to debug ip layout failed";
        throw runtime_error("Read sysfs failed");
    }
    LOG(INFO) << "Casting sysfs result to debug ip layout ...";
    debug_ip_layout* dbg = reinterpret_cast<debug_ip_layout*>(&data[0]);
    LOG(INFO) << "Type casting finished";
    LOG(INFO) << "Debug IP layout contains " << dbg->m_count << " entries";
    for (unsigned i = 0; i < dbg->m_count; ++i) {
        LOG(INFO) << "\t Showing debug_ip_layout[" << i << "]:";
        LOG(INFO) << "\t\t m_type: " << (unsigned)dbg->m_debug_ip_data[i].m_type;
        LOG(INFO) << "\t\t m_index: " << (unsigned)dbg->m_debug_ip_data[i].m_index;
        LOG(INFO) << "\t\t m_properties: 0x" << hex << (unsigned)dbg->m_debug_ip_data[i].m_properties << dec;
        LOG(INFO) << "\t\t m_major: " << (unsigned)dbg->m_debug_ip_data[i].m_major;
        LOG(INFO) << "\t\t m_minor: " << (unsigned)dbg->m_debug_ip_data[i].m_minor;
        LOG(INFO) << "\t\t m_base_address: 0x" << hex << (unsigned)dbg->m_debug_ip_data[i].m_base_address << dec;
        LOG(INFO) << "\t\t m_name: " << (char*)dbg->m_debug_ip_data[i].m_name;
    }
    LOG(INFO) << "Closing device[0] ...";
    xclClose(device_handle);
    LOG(INFO) << "device[0] closed";
    return 0;
}