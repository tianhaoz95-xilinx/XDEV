#include "gtest/gtest.h"
#include "xclhal2.h"

using ::testing::Test;
using ::testing::InitGoogleTest;

TEST(XRT_HAL, Probe) {
  int device_count = xclProbe();
  EXPECT_GT(device_count, 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}