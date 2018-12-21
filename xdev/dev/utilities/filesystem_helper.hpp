#ifndef __FILESYSTEM_HELPER__
#define __FILESYSTEM_HELPER__

#include "easylogging++.h"
#include <iostream>

using namespace std;

bool file_exist(const string& filename) {
    ifstream f(filename.c_str());
    return f.good();
}

#endif