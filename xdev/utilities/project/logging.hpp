/** @file */

#ifndef LOGGING_HPP_
#define LOGGING_HPP_

#include "easylogging++.h"
#include <string>

using namespace std;

void devlog(string msg) {
#ifdef DEMO
    LOG(INFO) << msg;
#endif
}

#endif