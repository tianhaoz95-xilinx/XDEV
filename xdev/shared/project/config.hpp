/** @file */

#ifndef XDEV_SHARED_PROJECT_CONFIG_HPP_
#define XDEV_SHARED_PROJECT_CONFIG_HPP_

// Copyright (C) 2019 Tianhao Zhou - All Rights Reserved

/**
 * The default path to the xclbin repository:
 * 
 * If no path to the xclbin repository has 
 * been specified in using environment variable
 * XCLBIN_REPO, then the code will assume that
 * it has been launched in the build directory
 * of the current project and look for xclbin
 * using the relative path ../darkside/farm/
 */
#define DEFAULT_XCLBIN_REPO "../darkside/farm/"

/**
 * This defines the name of the environment
 * variable that should give the location of
 * the xclbin repository
 */
#define XCLBIN_REPO_ENV "XCLBIN_REPO"

/**
 * The max size for debug IP layout:
 * 
 * The code has no prior knowledge of 
 * how big the debug IP layout file will
 * be, so we will give it a max size and
 * read all possible memory and cast
 * afterwards
 */
#define MAX_DEBUG_IP_LAYOUT_SIZE 65536

#define MAX_IP_LAYOUT_SIZE 65536

#endif  // XDEV_SHARED_PROJECT_CONFIG_HPP_

