add_custom_target(
    kernel_doc
    python -m mkdocs build
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs/test
)

add_dependencies(docs test_doc)