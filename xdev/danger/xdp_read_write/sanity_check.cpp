#include "profile/device/profile_ip_access.h"
#include "xclhal2.h"

int sanity_check(int argc, char* argv[]) {
    int device_count = xclProbe();
    int device_index = 0;
    xclDeviceHandle device_handle = xclOpen(device_index, "open_devices_demo.log", xclVerbosityLevel::XCL_INFO);
    auto profile_ip = xdp::ProfileIP(device_handle, 0);
    profile_ip.map();
    unsigned data[256];
    data[0] = 0;
    profile_ip.read(0, 3, data);
    std::cout << "Read back registers: 0x" << std::hex << data[0];
    return 0;
}

int main(int argc, char* argv[]) {
    return sanity_check(argc, argv);
}