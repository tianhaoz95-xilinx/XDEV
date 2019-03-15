/** @file */

#ifndef XDEV_SHARED_XRT_OPENCL_RETRIEVE_PLATFORM_HPP_
#define XDEV_SHARED_XRT_OPENCL_RETRIEVE_PLATFORM_HPP_

#include <string>
#include <vector>
#include "easylogging++.h"
#include "xrt/opencl/config.hpp"
#include "project/logging.hpp"

using std::string;
using std::vector;

vector<cl::Platform> retrieve_platform_by_index(int index);

vector<cl::Platform> retrieve_platform_by_name(string name);

vector<cl::Platform> retrieve_platform_by_index(int index) {
    vector<cl::Platform> platforms;
    vector<cl::Platform> matches;
    cl::Platform::get(&platforms);
    if (index < platforms.size()) {
        matches.push_back(platforms[index]);
    }
    return matches;
}

vector<cl::Platform> retrieve_platform_by_name(string name) {
    vector<cl::Platform> platforms;
    vector<cl::Platform> matches;
    cl::Platform::get(&platforms);
    for(size_t i = 0; i < platforms.size() ;i++) {
        cl::Platform platform = platforms[i];
        std::string platformName = platform.getInfo<CL_PLATFORM_NAME>();
        devlog("Found platform: " + platformName);
        if (platformName == name) {
            devlog("Found VALID platform: " + platformName + " , pushing to the platform array...");
            matches.push_back(platform);
        }
    }
    return matches;
}

#endif