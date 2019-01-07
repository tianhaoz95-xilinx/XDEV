/** @file */

#include "gtest/gtest.h"
#include "xclhal2.h"
#include "xclperf.h"
#include <iostream>

using namespace std;

using ::testing::Test;
using ::testing::InitGoogleTest;

/**
 * Test xclGetDebugProfileDeviceInfo
 * 
 * This function calls xclGetDebugProfileDeviceInfo 
 * from xclhal2.h and will expect device index to
 * match and all instance number be greater than
 * or equal to zero since there is no prior
 * knowledge about the instance number
 */
TEST(XRT_HAL, Debug_Profile_Device_Info) {
  int device_count = xclProbe();
  for (int i = 0; i < device_count; ++i) {
    string log_filename = "meta_example_device_" + to_string(i) + ".log";
    xclDeviceHandle device_handle = xclOpen(i, log_filename.c_str(), xclVerbosityLevel::XCL_INFO);
    xclDebugProfileDeviceInfo info;
    int err = xclGetDebugProfileDeviceInfo(device_handle, &info);
    if (err) {
        throw runtime_error("Read meta failed");
    }
    unsigned int device_index = (unsigned int)info.device_index;
    unsigned int user_instance = (unsigned int)info.user_instance;
    unsigned int device_type = (unsigned int)info.device_type;
    unsigned int mgmt_instance = (unsigned int)info.mgmt_instance;
    unsigned int nifd_instance = (unsigned int)info.nifd_instance;
    EXPECT_EQ(device_type, 2);
    EXPECT_EQ(device_index, i);
    EXPECT_GE(user_instance, 0);
    EXPECT_GE(mgmt_instance, 0);
    EXPECT_GE(nifd_instance, 0);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}