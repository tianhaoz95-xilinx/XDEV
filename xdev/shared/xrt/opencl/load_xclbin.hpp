/** @file */

#ifndef XDEV_SHARED_XRT_OPENCL_LOAD_XCLBIN_HPP_
#define XDEV_SHARED_XRT_OPENCL_LOAD_XCLBIN_HPP_

#include <string>
#include <vector>
#include <fstream>
#include "easylogging++.h"
#include "xrt/opencl/config.hpp"
#include "project/logging.hpp"

using std::string;
using std::vector;
using std::ifstream;
using std::runtime_error;

cl::Program load_xclbin_create_program(cl::Context context, vector<cl::Device> devices, string filename) {
    ifstream xclbin_file(filename, ifstream::binary);
    if (!xclbin_file.is_open()) {
        devlog("Cannot open the xclbin file, please check for typos in the path " + filename);
        throw runtime_error("Open xclbin failed");
    }
    xclbin_file.seekg (0, xclbin_file.end);
    unsigned nb = xclbin_file.tellg();
    xclbin_file.seekg (0, xclbin_file.beg);
    char *buf = new char [nb];
    xclbin_file.read(buf, nb);
    cl::Program::Binaries bins;
    bins.push_back({buf,nb});
    cl::Program program(context, devices, bins);
    delete [] buf;
    return program;
}

#endif