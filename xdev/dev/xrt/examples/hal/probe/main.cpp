#include "xclhal2.h"
#include "easylogging++.h"
#include <iostream>

using namespace std;

INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[]) {
    START_EASYLOGGINGPP(argc, argv);
    LOG(INFO) << "Starting Probe example ...";
    LOG(INFO) << "Probe about to start";
    int device_count = xclProbe();
    LOG(INFO) << "Probe finished";
    LOG(TRACE) << "Found " << device_count << " devices";
    return 0;
}