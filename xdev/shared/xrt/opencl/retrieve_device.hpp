/** @file */

#ifndef XDEV_SHARED_XRT_OPENCL_RETRIEVE_DEVICE_HPP_
#define XDEV_SHARED_XRT_OPENCL_RETRIEVE_DEVICE_HPP_

#include <string>
#include <vector>
#include "easylogging++.h"
#include "xrt/opencl/config.hpp"

using std::string;
using std::vector;

vector<cl::Device> retrieve_device_by_index(cl::Platform platform, int index);

vector<cl::Device> retrieve_device_by_name(cl::Platform platform, string name);

vector<cl::Device> retrieve_device_by_index(cl::Platform platform, int index) {
    std::vector<cl::Device> devices;
    std::vector<cl::Device> matches;
    platform.getDevices(CL_DEVICE_TYPE_ACCELERATOR, &devices);
    if (index < devices.size()) {
        matches.push_back(devices[index]);
    }
    return matches;
}

vector<cl::Device> retrieve_device_by_name(cl::Platform platform, string name) {
    std::vector<cl::Device> devices;
    std::vector<cl::Device> matches;
    platform.getDevices(CL_DEVICE_TYPE_ACCELERATOR, &devices);
    for (size_t i = 0 ; i < devices.size() ; i++){
        cl::Device device = devices[i];
        string current_name = device.getInfo<CL_DEVICE_NAME>();
        devlog("Found device: " + current_name);
        if (current_name == name){
            devlog("Found VALID device: " + current_name + " , pushing to the devices array...");
            matches.push_back(devices[i]);
        }
    }
    return matches;
}

#endif