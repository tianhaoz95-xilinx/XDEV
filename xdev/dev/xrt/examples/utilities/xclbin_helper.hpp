/** @file */

#ifndef __XCLBIN_HELPER__
#define __XCLBIN_HELPER__

#include "xclhal2.h"
#include "easylogging++.h"
#include "filesystem_helper.hpp"
#include "environment_helper.hpp"
#include "xclbin_repo_helper.hpp"
#include <iostream>
#include <boost/filesystem.hpp>

using namespace std;
namespace fs = boost::filesystem;

/**
 * Helper function to load xclbin onto device with hal API
 * 
 * @param [out] return none
 */
void load_xclbin_with_hal_api(string id /**< [in] the id of the xclbin */, 
                            xclDeviceHandle device_handle /**< [in] the hal device handle  */) {
    string xclbin_repo = search_xclbin_repository();
    fs::path xclbin_repo_root(xclbin_repo);
    fs::path xclbin_id(id);
    fs::path xclbin_full_path = xclbin_repo_root / xclbin_id;
    if (!file_exist(xclbin_full_path.string())) {
        LOG(ERROR) << xclbin_full_path.string() << " not exist on filesystem";
        throw runtime_error("xclbin file not exist");
    }
    ifstream ifs(xclbin_full_path.string());
    ifs.seekg(0, ifs.end);
    int size = ifs.tellg();
    ifs.seekg(0, ifs.beg);
    char *xclbin = new char[size];
    ifs.read(xclbin, size);
    if (strncmp(xclbin, "xclbin2", 8)) {
        LOG(ERROR) << "The header of the xclbin is not xclbin2";
        throw std::runtime_error("Invalid bitstream");
    }
    const xclBin *bitstream = (const xclBin *)xclbin;
    int err = 0;
    err = xclLockDevice(device_handle);
    if(err) {
        LOG(ERROR) << "Lock device failed with error code " << err;
        throw runtime_error("Lock device failed");
    }
    err = xclLoadXclBin(device_handle, bitstream);
    err = xclUnlockDevice(device_handle);
    if(err) {
        LOG(ERROR) << "Unlock device failed with error code " << err;
        throw runtime_error("Unlock device failed");
    }
    if (err) {
        delete [] xclbin;
        LOG(ERROR) << "Bitstream download failed with error code " << err;
        throw runtime_error("Bitstream download failed");
    }
    delete[] xclbin;
    LOG(INFO) << "Finished downloading bitstream " << xclbin_full_path.string();
    return;
}

#endif



