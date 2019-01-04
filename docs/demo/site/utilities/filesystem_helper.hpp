/** @file */

#ifndef __FILESYSTEM_HELPER__
#define __FILESYSTEM_HELPER__

#include "easylogging++.h"
#include <iostream>

using namespace std;

/**
 * Helper function for checking if a file exist
 * 
 * @param [out] return true if exist and false if not exist
 */
bool file_exist(const string& filename /**< [in] the file that needs to be checked */) {
    ifstream f(filename.c_str());
    return f.good();
}

#endif