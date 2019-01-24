/** @file */

// Copyright 2019 Tianhao Zhou

#ifndef XDEV_SHARED_PROJECT_LOGGING_HPP_
#define XDEV_SHARED_PROJECT_LOGGING_HPP_

#include <iostream>
#include "easylogging++.h"

using std::string;
using std::cout;
using std::endl;

void check_logging_status() {
#ifdef DEMO
    cout << "The code is compiled with DEMO" << endl;
#endif

#ifdef TEST
    cout << "The code is compiled with TEST" << endl;
#endif
}

void devlog(string msg) {
#ifdef DEMO
    LOG(INFO) << msg;
#endif
}

#endif  // XDEV_SHARED_PROJECT_LOGGING_HPP_

