/** @file */

// Copyright 2019 Tianhao Zhou

#include "xclhal2.h"
#include "easylogging++.h"
#include <iostream>

INITIALIZE_EASYLOGGINGPP

using namespace std;

/**
 * Example for probing devices
 */
int main(int argc, char* argv[]) {
    /**
     * \b START_EASYLOGGINGPP is the entry point to easyloggingpp
     * which only needs to be called once before any logging
     */
    START_EASYLOGGINGPP(argc, argv);
    LOG(INFO) << "Starting Probe example ...";
    LOG(INFO) << "Probe about to start";
    int device_count = xclProbe();
    LOG(INFO) << "Probe finished";
    LOG(TRACE) << "Found " << device_count << " devices";
    return 0;
}
