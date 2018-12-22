cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 14)

project(xdev)

include(cmake/googletest.cmake)
include(cmake/doxygen.cmake)
include(cmake/xrt.cmake)
include(cmake/logger.cmake)
include(cmake/boost.cmake)
include(cmake/package_add.cmake)

add_subdirectory(xdev)