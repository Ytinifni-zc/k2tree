enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/tests)
add_executable(test_libk2tree test_main.cc queries.cc)
target_link_libraries(test_libk2tree ${GTEST_LIBRARIES} rt gtest ${LIBK2TREE_NAME} ${Boost_LIBRARIES} pthread boost_system boost_filesystem)

set(TEST_DIR ${PROJECT_SOURCE_DIR}/tests)
message(${TEST_DIR})
file(GLOB TEST_SRCS RELATIVE ${TEST_DIR} "*.cc")
message("[Test_srcs]: ${TEST_SRCS}")
foreach(test ${TEST_SRCS})
    message("[###]: ${test}")
    get_filename_component(TEST_NAME ${test} NAME_WE)
    if(NOT (("${TEST_NAME}" STREQUAL "queries") OR ("${TEST_NAME}" STREQUAL "test_main")))
        message("[###]:Test_name - ${TEST_NAME}")
        add_executable(${TEST_NAME} ${TEST_DIR}/${test} ${TEST_DIR}/queries.cc)
        set_target_properties(${TEST_NAME}
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${BUILD_DIR}/tests"
            )
        target_link_libraries(${TEST_NAME} ${GTEST_LIBRARIES} ${COMMON_LIBRARIES} k2tree gd rt gtest ${LIBK2TREE_NAME} ${Boost_LIBRARIES} pthread boost_system boost_filesystem)
        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    endif()
endforeach()