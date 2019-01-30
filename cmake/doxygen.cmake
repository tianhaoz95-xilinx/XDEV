
if(${CMAKE_VERSION} VERSION_GREATER 3.9)
    message("CMake version is greater than 3.9. Will generate developer documentation automatically with Doxygen.")
    # check if Doxygen is installed
    find_package(Doxygen REQUIRED dot OPTIONAL_COMPONENTS mscgen dia)
    if (DOXYGEN_FOUND)
        # set input and output files
        set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs/developer)
        set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/xdev;
                            ${CMAKE_CURRENT_SOURCE_DIR}/darkside/kernel;
                            ${CMAKE_CURRENT_SOURCE_DIR}/third_party/XRT/src/runtime_src/driver/include)
        set(DOXYGEN_EXCLUDE_PATTERNS */gtest/*)
        set(DOXYGEN_FILE_PATTERNS *.cl;*.cpp;*.cc;*.c;*.hpp;*.h;DoxygenMain.txt;DoxygenConfig.txt)
        set(DOXYGEN_EXTENSION_MAPPING cl=C)
        set(DOXYGEN_ENABLE_PREPROCESSING YES)
        set(DOXYGEN_MACRO_EXPANSION YES)
        set(DOXYGEN_EXPAND_ONLY_PREDEF YES)
        set(DOXYGEN_PREDEFINED GEN_DOC)
        set(DOXYGEN_SOURCE_BROWSER YES)

        # note the option ALL which allows to build the docs together with the application
        doxygen_add_docs(developer_doc
            ${PROJECT_SOURCE_DIR}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generating developer documentation ...")
        add_dependencies(docs developer_doc)
    else ()
        message("Doxygen need to be installed to generate the doxygen documentation")
    endif ()
else()
    message("CMake version is less than 3.9. Developer documentation has to be manually generated with Doxygen if needed")
endif()