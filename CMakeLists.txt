cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 14)

project(xdev)

include(cmake/xrt.cmake)
include(cmake/logger.cmake)
include(cmake/boost.cmake)
include(cmake/googletest.cmake)
include(cmake/package_add.cmake)

# check if Doxygen is installed
find_package(Doxygen REQUIRED dot OPTIONAL_COMPONENTS mscgen dia)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs)
    set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/xdev)

    # note the option ALL which allows to build the docs together with the application
    doxygen_add_docs(doc_doxygen ALL
        ${PROJECT_SOURCE_DIR}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating documentation with Doxygen")
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

add_subdirectory(xdev)