#include "xclhal2.h"
#include "xclperf.h"
#include "xclbin.h"
#include "easylogging++.h"
#include "hal/xclbin_helper.hpp"
#include <iostream>

using namespace std;

INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[]) {
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
    char data[65536];
    LOG(INFO) << "Sysfs result buffer constructed ...";
    xclSysfsQuery query;
    LOG(INFO) << "Querying device[0] sysfs ...";
    query.size = 65536;
    xclReadSysfs(device_handle, query, (void*)data);
    LOG(INFO) << "Query device[0] sysfs finished ...";
    LOG(INFO) << "Casting sysfs result to debug ip layout ...";
    debug_ip_layout dbg;
    memcpy(&dbg, data, 65536);
    LOG(INFO) << "Type casting finished";
    LOG(INFO) << "Debug IP layout contains " << dbg.m_count << " entries";
    for (unsigned i = 0; i < dbg.m_count; ++i) {
        LOG(INFO) << "Showing debug_ip_layout[" << i << "]:";
        LOG(INFO) << "\t m_type: " << dbg.m_debug_ip_data[i].m_type;
        LOG(INFO) << "\t m_index: " << dbg.m_debug_ip_data[i].m_index;
        LOG(INFO) << "\t m_properties: " << hex << dbg.m_debug_ip_data[i].m_properties << dec;
        LOG(INFO) << "\t m_major: " << dbg.m_debug_ip_data[i].m_major;
        LOG(INFO) << "\t m_minor: " << dbg.m_debug_ip_data[i].m_minor;
        LOG(INFO) << "\t m_base_address: " << hex << dbg.m_debug_ip_data[i].m_base_address << dec;
        LOG(INFO) << "\t m_name: " << (char*)dbg.m_debug_ip_data[i].m_name;
    }
    LOG(INFO) << "Closing device[0] ...";
    xclClose(device_handle);
    LOG(INFO) << "device[0] closed";
    return 0;
}