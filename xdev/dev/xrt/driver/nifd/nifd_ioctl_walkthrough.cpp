/** @file */

#include <iostream>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include "easylogging++.h"
#include "xclhal2.h"
#include "xrt/driver/nifd/specification.hpp"
#include "xrt/driver/nifd/location.hpp"

INITIALIZE_EASYLOGGINGPP

using std::string;

int nifd_ioctl_walkthrough(int argc, char* argv[]) {
    START_EASYLOGGINGPP(argc, argv);

    string nifd_driver_path = get_nifd_driver_path();

    LOG(INFO) << "Probing device ...";
    int device_cnt = xclProbe();
    LOG(INFO) << "Number of device found: " << device_cnt;

    int device_index = 0;
    LOG(INFO) << "Opening device[" << device_index << "] ...";
    xclDeviceHandle device_handle = xclOpen(device_index, "nifd_ioctl_walkthrough.log", xclVerbosityLevel::XCL_INFO);
    LOG(INFO) << "Device[" << device_index << "] opened" ;

    LOG(INFO) << "Getting NIFD file descriptor ...";
    int nifd_driver_fd = open(nifd_driver_path.c_str(), O_RDWR);
    LOG(INFO) << "NIFD driver file descriptor return value: " << nifd_driver_fd;

    LOG(INFO) << "Switching control to NIFD ...";
    ioctl(nifd_driver_fd, NIFD_SWITCH_ICAP_TO_NIFD, 0);
    LOG(INFO) << "Control switched to NIFD";

    LOG(INFO) << "Switching control to PR ...";
    ioctl(nifd_driver_fd, NIFD_SWITCH_ICAP_TO_PR, 0);
    LOG(INFO) << "Control switched to PR";

    LOG(INFO) << "Closing NIFD file descriptor ...";
    close(nifd_driver_fd);
    LOG(INFO) << "NIFD file descriptor closed";

    xclClose(device_handle);
    return 0;
}

int main(int argc, char* argv[]) {
    return nifd_ioctl_walkthrough(argc, argv);
}