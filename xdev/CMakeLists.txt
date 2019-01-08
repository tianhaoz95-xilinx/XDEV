set(SHARED_UTIL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/utilities)
include_directories(${SHARED_UTIL_DIR})

add_subdirectory(dev)
add_subdirectory(test)