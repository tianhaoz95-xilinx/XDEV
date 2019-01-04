/** @file */

#ifndef __ENVIRONMENT_HELPER__
#define __ENVIRONMENT_HELPER__

#include "easylogging++.h"
#include <iostream>

using namespace std;

/**
 * This is helper function for safely getting
 * environment variables
 * 
 * @param [out] return the environment variable value
 */ 
string get_environment_variable(string name /**< [in] the environment variable name */) {
    char* raw = getenv("XCLBIN_REPO");
    if (raw) {
        string environment_variable(raw);
    } else {
        LOG(WARNING) << name << " environment variable does not exist";
        throw runtime_error("Environment variable not found");
    }
}

#endif