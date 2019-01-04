/** @file */

#ifndef __READ_SYSFS_HELPER__
#define __READ_SYSFS_HELPER__

#include "xclhal2.h"
#include "xclperf.h"
#include "xclbin.h"
#include "config.hpp"
#include "easylogging++.h"
#include <iostream>

using namespace std;

/**
 * Helper function for inspecting sysfs
 * 
 * This function reads sysfs with given
 * configuration to the API. This will
 * make testing all configurations easier
 * and reduces duplicated code for better
 * maintainability.
 */
void read_sysfs_with_config(
    xclDeviceHandle device_handle /**< [in] the handle of the device we want to query the sysfs (sysfs is 1 per device) */,
    bool read_all /**< [in] boolean that indicates if auto detect the size of the entry file */, 
    string subdev /**< [in] the name of the subdevice (e.g. xmc) */, 
    string entry /**< [in] the name of the entry (e.g. debug_ip_layout) */, 
    unsigned int size /**< [in] the size of the file to read, only used if read_all is set to false */,
    void* data /**< [in] the pointer to where the read back data should be written */)
{
    xclSysfsQuery query;
    strcpy(query.subdev, subdev.c_str());
    strcpy(query.entry, entry.c_str());
    query.read_all = read_all;
    query.size = size;
    int err = xclReadSysfs(device_handle, query, data);
    LOG(INFO) << "Query device[0] sysfs finished ...";
    if (err) {
        LOG(ERROR) << "Reading sysfs result failed";
        throw runtime_error("Read sysfs failed");
    }
}

#endif