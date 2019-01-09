/** @file */

// Copyright 2019 Tianhao Zhou

#ifndef XDEV_SHARED_PROJECT_FILESYSTEM_HPP_
#define XDEV_SHARED_PROJECT_FILESYSTEM_HPP_

#include <iostream>

#ifdef DEMO

#include "easylogging++.h"

#endif

#ifdef TEST

#include "gtest/gtest.h"

using ::testing::Test;
using ::testing::InitGoogleTest;

#endif

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

/**
 * 
 */
void check_if_file_exist(const string& filename /**< [in] the file that needs to be checked */) {
#ifdef DEMO
    if (!file_exist(filename)) {
        LOG(ERROR) << filename << " not exist on filesystem";
        throw runtime_error("xclbin file not exist");
    }
#endif

#ifdef TEST
    EXPECT_TRUE(file_exist(filename));
#endif
}

#endif  // XDEV_SHARED_PROJECT_FILESYSTEM_HPP_

