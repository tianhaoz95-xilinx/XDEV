/** @file */

#ifndef READ_SYSFS_HPP_
#define READ_SYSFS_HPP_

#include "xclhal2.h"
#include "xclperf.h"
#include "xclbin.h"
#include "project/config.hpp"
#include "easylogging++.h"
#include <iostream>
#include <fstream>

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
    string subdev /**< [in] the name of the subdevice (e.g. xmc) */, 
    string entry /**< [in] the name of the entry (e.g. debug_ip_layout) */, 
    unsigned int size /**< [in] the size of the file to read, only used if read_all is set to false */,
    void* data /**< [in] the pointer to where the read back data should be written */)
{
    char sysfs_path[256];
    int err = xclGetSysfsPath(device_handle, subdev.c_str(), entry.c_str(), sysfs_path, 256);
    LOG(INFO) << "Query device[0] sysfs finished ...";
    if (err) {
        LOG(ERROR) << "Reading sysfs path failed";
        throw runtime_error("Read sysfs path failed");
    }
    LOG(INFO) << "Sysfs full path: " << string(sysfs_path);
    ifstream fs(sysfs_path, ifstream::binary);
    if (fs.is_open()) {
        fs.read((char*)data, size);
        fs.close();
    } else {
        LOG(ERROR) << "Failed to open sysfs";
        throw runtime_error("Read sysfs failed");
    }
}

#endif