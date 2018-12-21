#ifndef __XCLBIN_HELPER__
#define __XCLBIN_HELPER__

#include "xclhal2.h"
#include "easylogging++.h"
#include <iostream>

using namespace std;

string search_xclbin_repository() {
    return "none";
}

void load_xclbin(string filename, xclDeviceHandle& device_handle) {
    /*
    std::ifstream ifs(filename);
    ifs.seekg(0, ifs.end);
    int size = ifs.tellg();
    ifs.seekg(0, ifs.beg);
    char *xclbin = new char[size];
    ifs.read(xclbin, size);
    */
    return;
}

#endif