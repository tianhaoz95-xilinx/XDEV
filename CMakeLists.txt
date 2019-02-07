cmake_minimum_required(VERSION 3.0.0)
if(POLICY CMP0057)
  cmake_policy(SET CMP0057 NEW)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

include(cmake/cov_config.cmake)

project(xdev)

include(cmake/googletest.cmake)
include(cmake/docs.cmake)
include(cmake/doxygen.cmake)
include(cmake/demo_doc.cmake)
include(cmake/xrt.cmake)
include(cmake/logger.cmake)
include(cmake/boost.cmake)
include(cmake/package_add.cmake)

add_subdirectory(xdev)