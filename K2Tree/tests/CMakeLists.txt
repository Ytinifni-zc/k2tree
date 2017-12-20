enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/tests)
add_executable(test_k2tree test_main.cc)
target_link_libraries(test_k2tree dacs gtest ${K2TREE_NAME} pthread sdsl divsufsort divsufsort64 async++ rt)

set(TEST_DIR ${PROJECT_SOURCE_DIR}/tests)
file(GLOB TEST_SRCS RELATIVE ${TEST_DIR} "*.cc" "tests_utils.h")
foreach(test ${TEST_SRCS})
    get_filename_component(TEST_NAME ${test} NAME_WE)
    if(NOT (("${TEST_NAME}" STREQUAL "queries") OR ("${TEST_NAME}" STREQUAL "test_main")))
        add_executable(${TEST_NAME} ${TEST_DIR}/${test})
        set_target_properties(${TEST_NAME}
                PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY "${BUILD_DIR}/tests"
                )
        target_link_libraries(${TEST_NAME} async++ dacs sdsl divsufsort divsufsort64 gtest gtest_main ${K2TREE_NAME} pthread rt)
        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    endif()
endforeach()
