/** @file */

// Copyright 2019 Tianhao Zhou

#ifndef XDEV_SHARED_PROJECT_ERROR_HPP_
#define XDEV_SHARED_PROJECT_ERROR_HPP_

#include <iostream>

using namespace std;

/**
 * Helper for handle error numbers
 */
void handle_errno(string msg, /**< [in] the message that should be shown given there is non-zero error */
                int err /**< [in] the error number returned from API */);

void handle_errno(string msg, int err) {
#ifdef DEMO
    if (err) {
        LOG(ERROR) << msg << ", error code: " << err;
        throw runtime_error(msg);
    }
#endif

#ifdef TEST
    EXPECT_EQ(err, 0);
#endif
}

#endif  // XDEV_SHARED_PROJECT_ERROR_HPP_

