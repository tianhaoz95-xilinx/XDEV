# XDEV

> So far, all the code and documentation in this project repository is meant for my personal usage only. There is no other purpose planned as of the date this README was updated.

Test field for card related development

[![Build Status](https://travis-ci.com/tianhaoz95-xilinx/XDEV.svg?branch=master)](https://travis-ci.com/tianhaoz95-xilinx/XDEV)
[![codecov](https://codecov.io/gh/tianhaoz95-xilinx/XDEV/branch/master/graph/badge.svg)](https://codecov.io/gh/tianhaoz95-xilinx/XDEV)
[![Coverage Status](https://coveralls.io/repos/github/tianhaoz95-xilinx/XDEV/badge.svg?branch=master)](https://coveralls.io/github/tianhaoz95-xilinx/XDEV?branch=master)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/c7903a4371574a128d1a9ce2469fa04e)](https://www.codacy.com/app/tianhao.zhou/XDEV?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=tianhaoz95-xilinx/XDEV&amp;utm_campaign=Badge_Grade)
[![CodeFactor](https://www.codefactor.io/repository/github/tianhaoz95-xilinx/XDEV/badge?style=flat-square)](https://www.codefactor.io/repository/github/tianhaoz95-xilinx/XDEV/badge?style=flat-square)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/tianhaoz95-xilinx/XDEV.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/tianhaoz95-xilinx/XDEV/alerts/)
[![Language grade: JavaScript](https://img.shields.io/lgtm/grade/javascript/g/tianhaoz95-xilinx/XDEV.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/tianhaoz95-xilinx/XDEV/context:javascript)

## Getting Started

### Quick Start

* Clone the repository. `git clone --recurse-submodules https://github.com/tianhaoz95-xilinx/XDEV.git`
* create a build directory in the project root directory. `mkdir build`
* `cd build`
* source the XRT build. `source /path/to/xrt/setup.sh` (please change this to your desired XRT location)
* `cmake ..` or `cmake3 ..` depending on which is in your PATH
* use `make help` to list all the test cases
* `make [the test case you want]` will build the preferred test case.
* `./bin/[path to the executable]` will launch the preferred test case binary.

### Documentation

[For XDEV Developers](https://tianhaoz95-xilinx.github.io/XDEV/developer/html/index.html) 

[For Dev Users](https://tianhaoz95-xilinx.github.io/XDEV/demo/site/index.html)

[For Kernel Users](https://tianhaoz95-xilinx.github.io/XDEV/kernel/site/index.html)

[For Test Users](https://tianhaoz95-xilinx.github.io/XDEV/test/site/index.html)

### Need Demo Code Snipet?

Examples make assumption that they are launched from build directory and will search data files using relative path if none is specified.

| Category         | Example/Test                                                                           |
|:----------------:|:--------------------------------------------------------------------------------------:|
| XRT/hal          | [sysfs api](./xdev/dev/xrt/examples/hal/sysfs)                                         |
| XRT/hal          | [probe api](./xdev/dev/xrt/examples/hal/probe)                                         |
| XRT/hal          | [debug profile device info api](./xdev/dev/xrt/examples/hal/debug_profile_device_info) |

### Need Kernels?

| Kernel                                         | Type     |
|:----------------------------------------------:|:--------:|
| [Copy Kernel](./darkside/kernel/copy/)         | OpenCL C |
| [Vector Add Kernel](./darkside/kernel/vadd/)   | OpenCL C |
| [Hello World Kernel](./darkside/kernel/hello/) | OpenCL C |

### Need Tests?
