add_custom_target(
    demo_doc
    python -m mkdocs build
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs/demo
)