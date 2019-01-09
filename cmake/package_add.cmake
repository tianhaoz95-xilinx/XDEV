macro(package_add_test TESTGROUP TESTNAME)
    add_executable(${TESTNAME} ${ARGN})
    set_target_properties(${TESTNAME}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test/${TESTGROUP}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test/${TESTGROUP}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test/${TESTGROUP}/bin"
    )
    target_link_libraries(${TESTNAME} pthread gtest gmock gtest_main ${XRT_CORE_LIB} ${XRT_OPENCL_LIB} ${Boost_LIBRARIES})
    add_test(${TESTNAME} ${CMAKE_BINARY_DIR}/test/${TESTGROUP}/bin/${TESTNAME})
    set_target_properties(${TESTNAME} PROPERTIES FOLDER test)
    target_compile_definitions(${TESTNAME} PUBLIC TEST)
endmacro()

macro(package_add_example EXAMPLEGROUP EXAMPLENAME)
    add_executable(${EXAMPLENAME} ${ARGN} ${LOGGER_DIR}/easylogging++.cc)
    set_target_properties(${EXAMPLENAME}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/utility_library/${EXAMPLEGROUP}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/utility_library/${EXAMPLEGROUP}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${EXAMPLEGROUP}"
    )
    target_link_libraries(${EXAMPLENAME} pthread ${XRT_CORE_LIB} ${XRT_OPENCL_LIB} ${Boost_LIBRARIES})
    set_target_properties(${EXAMPLENAME} PROPERTIES FOLDER dev)
    target_compile_definitions(${EXAMPLENAME} PUBLIC DEMO)
endmacro()