/** @file */

/**
 * This header file should be included before 
 * any other OpenCL resources because it contains
 * preprocessor options
 */

#ifndef XDEV_SHARED_XRT_OPENCL_CONFIG_HPP_
#define XDEV_SHARED_XRT_OPENCL_CONFIG_HPP_

#define CL_HPP_CL_1_2_DEFAULT_BUILD
#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#define CL_HPP_ENABLE_PROGRAM_CONSTRUCTION_FROM_ARRAY_COMPATIBILITY 1

#include <CL/cl2.hpp>

#endif

