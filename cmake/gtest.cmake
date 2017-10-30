CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

set(GTEST_ROOT ${PROJECT_SOURCE_DIR}/gtest)
add_subdirectory(${GTEST_ROOT})
set(GTEST_INCLUDE_DIR ${GTEST_ROOT}/include)
set(GTEST_LIBRARIES gtest gtest_main)
include_directories(${GTEST_INCLUDE_DIR})