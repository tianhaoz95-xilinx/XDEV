# XDEV
Test field for XRT development

[![Build Status](https://travis-ci.com/tianhaoz95-xilinx/XDEV.svg?branch=master)](https://travis-ci.com/tianhaoz95-xilinx/XDEV)
[![codecov](https://codecov.io/gh/tianhaoz95-xilinx/XDEV/branch/master/graph/badge.svg)](https://codecov.io/gh/tianhaoz95-xilinx/XDEV)
[![Coverage Status](https://coveralls.io/repos/github/tianhaoz95-xilinx/XDEV/badge.svg?branch=master)](https://coveralls.io/github/tianhaoz95-xilinx/XDEV?branch=master)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/c7903a4371574a128d1a9ce2469fa04e)](https://www.codacy.com/app/tianhao.zhou/XDEV?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=tianhaoz95-xilinx/XDEV&amp;utm_campaign=Badge_Grade)
[![CodeFactor](https://www.codefactor.io/repository/github/tianhaoz95-xilinx/XDEV/badge?style=flat-square)](https://www.codefactor.io/repository/github/tianhaoz95-xilinx/XDEV/badge?style=flat-square)

## Getting Started

### Documentation

[For Developers](https://tianhaoz95-xilinx.github.io/XDEV/html/index.html)

### Need a demo code snipet?

Examples make assumption that they are launched from build directory and will search data files using relative path if none is specified.

| Category         | Example/Test                                                                           |
|:----------------:|:--------------------------------------------------------------------------------------:|
| XRT/hal          | [sysfs api](./xdev/dev/xrt/examples/hal/sysfs)                                         |
| XRT/hal          | [probe api](./xdev/dev/xrt/examples/hal/probe)                                         |
| XRT/hal          | [debug profile device info api](./xdev/dev/xrt/examples/hal/debug_profile_device_info) |

### Need a kernel?

| Kernel                                         | Type     |
|:----------------------------------------------:|:--------:|
| [Copy Kernel](./darkside/kernel/copy/)         | OpenCL C |
| [Vector Add Kernel](./darkside/kernel/vadd/)   | OpenCL C |
| [Hello World Kernel](./darkside/kernel/hello/) | OpenCL C |

### Need a test?
