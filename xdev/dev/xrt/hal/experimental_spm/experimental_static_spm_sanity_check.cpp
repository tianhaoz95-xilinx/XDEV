/** @file */

// Copyright 2019 Tianhao Zhou

#include "xclhal2.h"
#include "easylogging++.h"
#include <iostream>

INITIALIZE_EASYLOGGINGPP

using namespace std;

/**
 * Example for opening devices
 */
int experimental_static_spm_sanity_check(int argc, char* argv[]) {
    unsigned long xdma_spm_addr = 0x00270000;
    unsigned long p2p_spm_addr = 0x00280000;
    unsigned long kdma_spm_addr = 0x00290000;
    LOG(INFO) << "Starting Probe example ...";
    LOG(INFO) << "Probe about to start";
    int device_count = xclProbe();
    LOG(INFO) << "Probe finished";
    LOG(TRACE) << "Found " << device_count << " devices";
    int device_index = 0;
    LOG(INFO) << "Opening device[" << device_index << "] ...";
    xclDeviceHandle device_handle = xclOpen(device_index, "experimental_xdma_spm_hal_log.log", xclVerbosityLevel::XCL_INFO);
    LOG(INFO) << "Device[" << device_index << "] opened" ;

    unsigned size = 0;
    unsigned int spm_size = 10;
    LOG(INFO) << "Reading the SPM attached to XDMA engine ...";
    unsigned int xdma_buf[256];
    size = xclRead(device_handle, XCL_ADDR_SPACE_DEVICE_PERFMON, xdma_spm_addr, (void*)xdma_buf, spm_size * sizeof(unsigned int));
    if (size < 0) {
        throw runtime_error("unmanaged read xdma spm failed");
    }
    string xdma_spm_readback = "XDMA SPM values: ";
    for (int i = 0; i < spm_size; ++i) {
        stringstream convert;
        convert << "0x" << hex << xdma_buf[i] << " ";
        xdma_spm_readback += convert.str();
    }
    LOG(INFO) << xdma_spm_readback;
    LOG(INFO) << "Reading the SPM attached to KDMA engine ...";
    unsigned int kdma_buf[256];
    size = xclRead(device_handle, XCL_ADDR_SPACE_DEVICE_PERFMON, kdma_spm_addr, (void*)kdma_buf, spm_size * sizeof(unsigned int));
    if (size < 0) {
        throw runtime_error("unmanaged read kdma spm failed");
    }
    string kdma_spm_readback = "KDMA SPM values: ";
    for (int i = 0; i < spm_size; ++i) {
        stringstream convert;
        convert << "0x" << hex << kdma_buf[i] << " ";
        kdma_spm_readback += convert.str();
    }
    LOG(INFO) << kdma_spm_readback;
    LOG(INFO) << "Reading the SPM attached to P2P engine ...";
    unsigned int p2p_buf[256];
    size = xclRead(device_handle, XCL_ADDR_SPACE_DEVICE_PERFMON, p2p_spm_addr, (void*)p2p_buf, spm_size * sizeof(unsigned int));
    if (size < 0) {
        throw runtime_error("unmanaged read p2p spm failed");
    }
    string p2p_spm_readback = "P2P SPM values: ";
    for (int i = 0; i < spm_size; ++i) {
        stringstream convert;
        convert << "0x" << hex << p2p_buf[i] << " ";
        p2p_spm_readback += convert.str();
    }
    LOG(INFO) << p2p_spm_readback;
    unsigned int write_to_control_reg = 0x1;
    LOG(INFO) << "Writing 0x1 to the P2P SPM control register ...";
    size = xclWrite(device_handle, XCL_ADDR_SPACE_DEVICE_PERFMON, p2p_spm_addr + 0x8, (void*)(&write_to_control_reg), sizeof(unsigned int));
    if (size < 0) {
        throw runtime_error("unmanaged read p2p spm failed");
    }
    size = xclRead(device_handle, XCL_ADDR_SPACE_DEVICE_PERFMON, p2p_spm_addr, (void*)p2p_buf, spm_size * sizeof(unsigned int));
    if (size < 0) {
        throw runtime_error("unmanaged read p2p spm failed");
    }
    p2p_spm_readback = "P2P SPM values: ";
    for (int i = 0; i < spm_size; ++i) {
        stringstream convert;
        convert << "0x" << hex << p2p_buf[i] << " ";
        p2p_spm_readback += convert.str();
    }
    LOG(INFO) << p2p_spm_readback;
    LOG(INFO) << "Writing 0x5 to the P2P SPM control register ...";
    write_to_control_reg = 0x5;
    size = xclWrite(device_handle, XCL_ADDR_SPACE_DEVICE_PERFMON, p2p_spm_addr + 0x8, (void*)(&write_to_control_reg), sizeof(unsigned int));
    if (size < 0) {
        throw runtime_error("unmanaged read p2p spm failed");
    }
    size = xclRead(device_handle, XCL_ADDR_SPACE_DEVICE_PERFMON, p2p_spm_addr, (void*)p2p_buf, spm_size * sizeof(unsigned int));
    if (size < 0) {
        throw runtime_error("unmanaged read p2p spm failed");
    }
    LOG(INFO) << "Closing device[0] ...";
    xclClose(device_handle);
    LOG(INFO) << "device[0] closed";
    return 0;
}

int main(int argc, char* argv[]) {
    START_EASYLOGGINGPP(argc, argv);
    return experimental_static_spm_sanity_check(argc, argv);
}
