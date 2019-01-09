# Sysfs hal API example

> This example uses the minimum code possible (so that it is most likely a single point of failure) to invoke a sysfs hal API to read the debug IP layout.

## Dependencies

* dev utilities at `xdev/dev/utilities`
* xrt utilities at `xdev/dev/xrt/utilities`
* hello_triple_compute_unit kernel

## Usage

1. go to project root directory
2. create build directory for cmake by `mkdir build` and `cd build`
3. prepare cmake by `cmake ..`
4. make only this example `make sysfs` (`make -j8` will make all the examples)
5. launch the example executable by `./bin/xrt/hal/sysfs` (The code assumes that it will be launched from build directory and will look for data relative to this directory if no environment variables are specified)