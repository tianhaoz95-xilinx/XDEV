cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 14)

project(xdev)

set(XRT_ROOT $ENV{XILINX_XRT})
include_directories(${XRT_ROOT}/include)
find_library(XRT_LIB xrt_core HINTS ${XRT_ROOT}/lib)

find_package(Boost 1.45 COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(LOGGER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/easyloggingpp/src)
include_directories(${LOGGER_DIR})

enable_testing()
add_subdirectory("${PROJECT_SOURCE_DIR}/third_party/googletest" "third_party/googletest")

mark_as_advanced(
    BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
    gmock_build_tests gtest_build_samples gtest_build_tests
    gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

set_target_properties(gtest PROPERTIES FOLDER third_party)
set_target_properties(gtest_main PROPERTIES FOLDER third_party)
set_target_properties(gmock PROPERTIES FOLDER third_party)
set_target_properties(gmock_main PROPERTIES FOLDER third_party)

macro(package_add_test TESTGROUP TESTNAME)
    add_executable(${TESTNAME} ${ARGN})
    set_target_properties(${TESTNAME}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test/${TESTGROUP}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test/${TESTGROUP}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test/${TESTGROUP}/bin"
    )
    target_link_libraries(${TESTNAME} gtest gmock gtest_main ${XRT_LIB} ${Boost_LIBRARIES})
    add_test(${TESTNAME} ${CMAKE_BINARY_DIR}/test/${TESTGROUP}/bin/${TESTNAME})
    set_target_properties(${TESTNAME} PROPERTIES FOLDER test)
endmacro()

macro(package_add_example EXAMPLEGROUP EXAMPLENAME)
    add_executable(${EXAMPLENAME} ${ARGN} ${LOGGER_DIR}/easylogging++.cc)
    set_target_properties(${EXAMPLENAME}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/utility_library/${EXAMPLEGROUP}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/utility_library/${EXAMPLEGROUP}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${EXAMPLEGROUP}"
    )
    target_link_libraries(${EXAMPLENAME} ${XRT_LIB} ${Boost_LIBRARIES})
    set_target_properties(${EXAMPLENAME} PROPERTIES FOLDER dev)
endmacro()

add_subdirectory(xdev)