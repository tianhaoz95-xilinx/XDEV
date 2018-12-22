/** @file */

#include "xclhal2.h"
#include "easylogging++.h"
#include <iostream>

INITIALIZE_EASYLOGGINGPP

using namespace std;

int main(int argc, char* argv[]) {
    START_EASYLOGGINGPP(argc, argv);
    LOG(INFO) << "Starting Probe example ...";
    LOG(INFO) << "Probe about to start";
    int device_count = xclProbe();
    LOG(INFO) << "Probe finished";
    LOG(TRACE) << "Found " << device_count << " devices";
    return 0;
}