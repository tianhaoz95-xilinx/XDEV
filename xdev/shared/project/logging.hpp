/** @file */

// Copyright 2019 Tianhao Zhou

#ifndef XDEV_SHARED_PROJECT_LOGGING_HPP_
#define XDEV_SHARED_PROJECT_LOGGING_HPP_

#include "easylogging++.h"
#include <string>

using std::string;

void devlog(string msg) {
#ifdef DEMO
    LOG(INFO) << msg;
#endif
}

#endif  // XDEV_SHARED_PROJECT_LOGGING_HPP_

