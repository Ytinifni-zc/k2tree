enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/tests)

set(TEST_DIR ${PROJECT_SOURCE_DIR}/tests)
file(GLOB TEST_SRCS RELATIVE ${TEST_DIR} "*.cc")
foreach(test ${TEST_SRCS})
    get_filename_component(TEST_NAME ${test} NAME_WE)
    if(NOT (("${TEST_NAME}" STREQUAL "queries") OR ("${TEST_NAME}" STREQUAL "test_main")))
        add_executable(${TEST_NAME} ${TEST_DIR}/${test})
        set_target_properties(${TEST_NAME}
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${BUILD_DIR}/tests"
            )
        target_link_libraries(${TEST_NAME} ${GTEST_LIBRARIES} gtest ${LIBK2TREE_NAME})
        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    endif()
endforeach()