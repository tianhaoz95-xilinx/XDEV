/** @file */

// Copyright 2019 Tianhao Zhou

#ifndef XDEV_SHARED_XRT_HAL_LOAD_XCLBIN_HPP_
#define XDEV_SHARED_XRT_HAL_LOAD_XCLBIN_HPP_

#include "xclhal2.h"
#include "project/filesystem.hpp"
#include "project/config.hpp"
#include "project/error.hpp"
#include "project/environment.hpp"
#include <iostream>
#include <boost/filesystem.hpp>

using namespace std;
namespace fs = boost::filesystem;

/**
 * This function will look at the XCLBIN_REPO environment
 * variable. If not found, it will assume the example
 * executable is launched from build directory and try
 * to find darkside/farm using relative path.
 * 
 * @param [out] return directory for potential xclbin repository
 */
string search_xclbin_repository();

/**
 * Check xclbin file header
 */
void check_xclbin_file_header(char* xclbin /**< [in] the memory where the xclbin file has been read in */);

/**
 * Helper function to load xclbin onto device with hal API
 * 
 * @param [out] return none
 */
void load_xclbin(string id /**< [in] the id of the xclbin */, 
                xclDeviceHandle device_handle /**< [in] the hal device handle  */);

void load_xclbin(string id, xclDeviceHandle device_handle) {
    string xclbin_repo = search_xclbin_repository();
    fs::path xclbin_repo_root(xclbin_repo);
    fs::path xclbin_id(id);
    fs::path xclbin_full_path = xclbin_repo_root / xclbin_id;
    check_if_file_exist(xclbin_full_path.string());
    ifstream ifs(xclbin_full_path.string());
    ifs.seekg(0, ifs.end);
    int size = ifs.tellg();
    ifs.seekg(0, ifs.beg);
    char *xclbin = new char[size];
    ifs.read(xclbin, size);
    check_xclbin_file_header(xclbin);
    const xclBin *bitstream = (const xclBin *)xclbin;
    int err = 0;
    err = xclLockDevice(device_handle);
    handle_errno("Lock device failed", err);
    err = xclLoadXclBin(device_handle, bitstream);
    handle_errno("Bitstream download failed", err);
    err = xclUnlockDevice(device_handle);
    handle_errno("Unlock device failed", err);
    delete[] xclbin;
    LOG(INFO) << "Finished downloading bitstream " << xclbin_full_path.string();
    return;
}

string search_xclbin_repository() {
    string xclbin_repo;
    try {
        xclbin_repo = get_environment_variable(XCLBIN_REPO_ENV);
    } catch (runtime_error& e) {
#ifdef DEMO
        LOG(WARNING) << e.what();
        LOG(WARNING) << "Assuming running from build directory";
#endif
        xclbin_repo = DEFAULT_XCLBIN_REPO;
    } catch (...) {
#ifdef DEMO
        LOG(ERROR) << "Unknown error happend while searching for xclbin repository";
        LOG(WARNING) << "Assuming running from build directory";
#endif
        xclbin_repo = DEFAULT_XCLBIN_REPO;
    }
    return xclbin_repo;
}

void check_xclbin_file_header(char* xclbin) {
#ifdef DEMO
    if (strncmp(xclbin, "xclbin2", 8)) {
        LOG(ERROR) << "The header of the xclbin is not xclbin2";
        throw std::runtime_error("Invalid bitstream");
    }
#endif

#ifdef TEST
    EXPECT_EQ(strncmp(xclbin, "xclbin2", 8), 0);
#endif
}

#endif  // XDEV_SHARED_XRT_HAL_LOAD_XCLBIN_HPP_

