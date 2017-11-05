CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

set(GTEST_ROOT ${PROJECT_SOURCE_DIR}/gtest)
add_subdirectory(${GTEST_ROOT})
set(GTEST_INCLUDE_DIR ${GTEST_ROOT}/include)
set(GTEST_LIBRARIES gtest gtest_main)
include_directories(${GTEST_INCLUDE_DIR})

#enable_testing()
#set(TEST_DIR ${PROJECT_SOURCE_DIR}/tests)
#file(GLOB TEST_SRCS RELATIVE ${TEST_DIR} "tests/*.cc")
#foreach(test ${TEST_SRCS})
#    get_filename_component(TEST_NAME ${test} NAME_WE)
#    add_executable(${TEST_NAME} ${TEST_DIR}/${test})
#    set_target_properties(${TEST_NAME}
#        PROPERTIES
#        RUNTIME_OUTPUT_DIRECTORY "${BUILD_DIR}/test"
#        )
#    target_link_libraries(${TEST_NAME} ${GTEST_LIBRARIES} ${COMMON_LIBRARIES} k2tree rt gtest ${LIBK2TREE_NAME} ${Boost_LIBRARIES} pthread boost_system boost_filesystem)
#    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
#endforeach()