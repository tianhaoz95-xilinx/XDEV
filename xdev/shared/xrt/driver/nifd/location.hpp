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
    return "/dev/dri/renderD129";
}

string get_nifd_driver_path() {
    return "/dev/nifd.m45824";
}

string get_xclbin_path() {
    return "/proj/isi_group/isim/tianhaoz/Misc/nifd_xclbin/binary_container_with_better_debug_data.xclbin";
}

#endif  // XDEV_SHARED_XRT_DRIVER_NIFD_LOCATION_HPP_

