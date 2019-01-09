set(XRT_ROOT $ENV{XILINX_XRT})
include_directories(${XRT_ROOT}/include)
find_library(XRT_CORE_LIB xrt_core HINTS ${XRT_ROOT}/lib)
find_library(XRT_OPENCL_LIB xilinxopencl HINTS ${XRT_ROOT}/lib)