set(XRT_ROOT $ENV{XILINX_XRT})
include_directories(${XRT_ROOT}/include)
find_library(XRT_LIB xrt_core HINTS ${XRT_ROOT}/lib)