/** @file */

#include "gtest/gtest.h"
#include "xclhal2.h"

using ::testing::Test;
using ::testing::InitGoogleTest;

/**
 * Test Sysfs Path API
 */
TEST(XRT_HAL, Sysfs_Path_API) {
  int device_count = xclProbe();
  if (device_count == 0) {
      return;
  }
  return
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}