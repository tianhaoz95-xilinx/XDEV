/** @file */

// Copyright 2019 Tianhao Zhou

#ifndef XDEV_SHARED_XRT_DRIVER_NIFD_SPECIFICATION_HPP_
#define XDEV_SHARED_XRT_DRIVER_NIFD_SPECIFICATION_HPP_

enum NIFDCommand {
  NIFD_ACQUIRE_CU             = 0,
  NIFD_RELEASE_CU             = 1,
  NIFD_QUERY_CU               = 2,
  NIFD_READBACK_VARIABLE      = 3,
  NIFD_SWITCH_ICAP_TO_NIFD    = 4,
  NIFD_SWITCH_ICAP_TO_PR      = 5,
  NIFD_ADD_BREAKPOINTS        = 6,
  NIFD_REMOVE_BREAKPOINTS     = 7,
  NIFD_CHECK_STATUS           = 8,
  NIFD_QUERY_XCLBIN           = 9,
  NIFD_STOP_CONTROLLED_CLOCK  = 10,
  NIFD_START_CONTROLLED_CLOCK = 11,
  NIFD_SWITCH_CLOCK_MODE      = 12
};

enum XCLMGMT_IOC_TYPES {
	XCLMGMT_IOC_INFO,
	XCLMGMT_IOC_ICAP_DOWNLOAD,
	XCLMGMT_IOC_FREQ_SCALE,
	XCLMGMT_IOC_OCL_RESET,
	XCLMGMT_IOC_HOT_RESET,
	XCLMGMT_IOC_REBOOT,
	XCLMGMT_IOC_ICAP_DOWNLOAD_AXLF,
	XCLMGMT_IOC_ERR_INFO,
	XCLMGMT_IOC_MAX,
	XCLMGMT_RESET_NIFD
};

#define XCLMGMT_RESETNIFD _IO(XCLMGMT_IOC_MAGIC,XCLMGMT_RESET_NIFD)

#define NIFD_FREE_RUNNING_MODE 1
#define NIFD_STEPPING_MODE     2

#endif  // XDEV_SHARED_XRT_DRIVER_NIFD_SPECIFICATION_HPP_

