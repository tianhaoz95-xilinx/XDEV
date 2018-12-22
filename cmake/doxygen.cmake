
if(${CMAKE_VERSION} VERSION_GREATER 3.9)
    message("CMake version is greater than 3.9. Will generate developer documentation automatically with Doxygen.")
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
else()
    message("CMake version is less than 3.9. Developer documentation has to be manually generated with Doxygen if needed")
endif()