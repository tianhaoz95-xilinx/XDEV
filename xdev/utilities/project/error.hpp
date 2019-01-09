/** @file */

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <iostream>

using namespace std;

/**
 * Helper for handle error numbers
 */
void handle_errno(string msg, /**< [in] the message that should be shown given there is non-zero error */
                int err /**< [in] the error number returned from API */);

void handle_errno(string msg, int err) {
#ifdef DEMO
    if(err) {
        LOG(ERROR) << msg << ", error code: " << err;
        throw runtime_error("Unlock device failed");
    }
#endif

#ifdef TEST
    EXPECT_EQ(err, 0);
#endif
}

#endif