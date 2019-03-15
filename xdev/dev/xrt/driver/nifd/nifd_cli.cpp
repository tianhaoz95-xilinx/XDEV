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
using std::cin;
using std::cout;
using std::endl;

int nifd_driver_fd = -1;

bool keep_going = true;

bool open_nifd_driver() {
    cout << "Path to the NIFD charactor device: ";
    string nifd_dev_path;
    cin >> nifd_dev_path;
    nifd_driver_fd = open(nifd_dev_path.c_str(), O_RDWR);
    LOG(INFO) << "Opening NIFD driver returned with file descriptor: " << nifd_driver_fd;
    return true;
}

bool close_nifd_driver() {
    LOG(INFO) << "Closing NIFD file descriptor ...";
    close(nifd_driver_fd);
    LOG(INFO) << "NIFD file descriptor closed";
    nifd_driver_fd = -1;
    return true;
}

bool switch_icap_to_nifd() {
    int ret = ioctl(nifd_driver_fd, NIFD_SWITCH_ICAP_TO_NIFD, 0);
    LOG(INFO) << "Switching ICAP to NIFD returned with code: " << ret;
    return true;
}

bool switch_icap_to_pr() {
    int ret = ioctl(nifd_driver_fd, NIFD_SWITCH_ICAP_TO_PR, 0);
    LOG(INFO) << "Switching ICAP to PR returned with code: " << ret;
    return true;
}

bool stop_clock() {
    int ret = ioctl(nifd_driver_fd, NIFD_STOP_CONTROLLED_CLOCK, 0);
    LOG(INFO) << "Stopping clock returned with code: " << ret;
    return true;
}

bool start_clock_free_running() {
    unsigned int mode = NIFD_FREE_RUNNING_MODE;
    int ret = ioctl(nifd_driver_fd, NIFD_START_CONTROLLED_CLOCK, &mode);
    LOG(INFO) << "Starting clock in free running mode returned with code: " << ret;
    return true;
}

bool exit_nifd_cli() {
    return false;
}

bool unknown_command() {
    LOG(INFO) << "Unknown command :(";
    return true;
}

bool help() {
    cout << "Help: " << endl;
    cout << "open_nifd_driver" << endl;
    cout << "close_nifd_driver" << endl;
    cout << "switch_icap_to_nifd" << endl;
    cout << "switch_icap_to_pr" << endl;
    cout << "stop_clock" << endl;
    cout << "start_clock_free_running" << endl;
}

bool exec_nifd_command(string command) {
    if (command == "switch_icap_to_nifd") {
        return switch_icap_to_nifd();
    } else if (command == "open_nifd_driver") {
        return open_nifd_driver();
    } else if (command == "switch_icap_to_pr") {
        return switch_icap_to_pr();
    } else if (command == "stop_clock") {
        return stop_clock();
    } else if (command == "start_clock_free_running") {
        return start_clock_free_running();
    } else if (command == "close_nifd_driver") {
        return close_nifd_driver();
    } else if (command == "help") {
        return help();
    } else {
        return unknown_command();
    }
}

int nifd_cli(int argc, char* argv[]) {
    while (keep_going) {
        cout << "NIFD command to execute: ";
        string command;
        cin >> command;
        keep_going = exec_nifd_command(command);
    }
    return 0;
}

int main(int argc, char* argv[]) {
    START_EASYLOGGINGPP(argc, argv);
    return nifd_cli(argc, argv);
}