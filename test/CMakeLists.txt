file(GLOB TEST_SOURCES "${PROJECT_SOURCE_DIR}/test/*.cpp")

##########################################
# "make test ..."
##########################################
foreach (test_source ${TEST_SOURCES})
    # Create a human readable name.
    get_filename_component(test_filename ${test_source} NAME)
    string(REPLACE ".cpp" "" test_name ${test_filename})

    # Add the test target separately and as part of "make check-tests".
    add_executable(${test_name} EXCLUDE_FROM_ALL ${test_source})
    # add_dependencies(build-tests ${test_name})
    # add_dependencies(check-tests ${test_name})

    target_link_libraries(${test_name} lib_shared)

    # Set test target properties and dependencies.
    set_target_properties(${test_name}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        COMMAND ${test_name}
    )

    message(STATUS "CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")

endforeach(test_source ${TEST_SOURCES})