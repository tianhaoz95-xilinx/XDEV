/** @file */

// Copyright 2019 Tianhao Zhou

#ifndef XDEV_SHARED_XRT_DRIVER_NIFD_LOCATION_HPP_
#define XDEV_SHARED_XRT_DRIVER_NIFD_LOCATION_HPP_

#include <string>

using std::string;

/**
 * Helper function for getting the
 * path to the xdma driver under /dev
 */
string get_xdma_driver_path();

/**
 * Helper function for getting the
 * path to the nifd driver udnder /dev
 */
string get_nifd_driver_path();

/**
 * Helper function for getting the desired
 * xclbin that is nifd testing related
 */
string get_xclbin_path();

string get_xdma_driver_path() {
    return "/dev/dri/renderD128";
}

string get_management_driver_path() {
    return "/dev/xclmgmt45824";
}

string get_nifd_driver_path() {
    return "/dev/nifd_pri.m45824";
}

string get_xclbin_path() {
    return "/home/xsjbrd6/Desktop/darkside/farm/alveo_u200_nifd_experimental/vadd_full_connection/vadd_kernel_hw_all.xclbin";
}

#endif  // XDEV_SHARED_XRT_DRIVER_NIFD_LOCATION_HPP_

