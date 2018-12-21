#ifndef __XCLBIN_REPO_HELPER__
#define __XCLBIN_REPO_HELPER__

#include <iostream>
#include "xrt/config.hpp"

using namespace std;

string search_xclbin_repository() {
    string xclbin_repo;
    try {
        xclbin_repo = get_environment_variable(XCLBIN_REPO_ENV);
    } catch (runtime_error& e) {
        LOG(WARNING) << e.what();
        LOG(WARNING) << "Assuming running from build directory";
        xclbin_repo = DEFAULT_XCLBIN_REPO;
    } catch (...) {
        LOG(ERROR) << "Unknown error happend while searching for xclbin repository";
        LOG(WARNING) << "Assuming running from build directory";
        xclbin_repo = DEFAULT_XCLBIN_REPO;
    }
    return xclbin_repo;
}

#endif