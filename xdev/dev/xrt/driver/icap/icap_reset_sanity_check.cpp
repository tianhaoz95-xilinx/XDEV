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

int icap_reset_sanity_check(int argc, char* argv[]) {
    LOG(INFO) << "Getting NIFD file descriptor ...";
    int nifd_driver_fd = open(nifd_driver_path.c_str(), O_RDWR);
    LOG(INFO) << "NIFD driver file descriptor return value: " << nifd_driver_fd;

    LOG(INFO) << "Switching control to NIFD ...";
    ioctl(nifd_driver_fd, NIFD_SWITCH_ICAP_TO_NIFD, 0);
    LOG(INFO) << "Control switched to NIFD";

    LOG(INFO) << "Closing NIFD file descriptor ...";
    close(nifd_driver_fd);
    LOG(INFO) << "NIFD file descriptor closed";
}

int main(int argc, char* argv[]) {
    START_EASYLOGGINGPP(argc, argv);
    return icap_reset_sanity_check(argc, argv);
}