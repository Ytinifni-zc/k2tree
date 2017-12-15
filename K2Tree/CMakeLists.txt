cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)
project(K2Tree)

#add_definitions( -DDebug  )
#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(gtest)
#include(flycheck_clang.cmake)
#write_dir_locals_el(${CMAKE_CURRENT_SOURCE_DIR})
#include(sdsl)

set(K2TREE_NAME "k2tree")
set(CMAKE_CXX_STANDARD 11)
set(BUILD_DIR ${PROJECT_SOURCE_DIR}/_build)
set(THIRDPARTY ${CMAKE_SOURCE_DIR}/thirdparty)

include(${THIRDPARTY}/asyncplusplus/cmake/Async++.cmake)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

include_directories(${THIRDPARTY}/gtest/include)
include_directories(${THIRDPARTY}/libsdsl/include)
include_directories(${THIRDPARTY}/dacs/include)
include_directories(${THIRDPARTY}/asyncplusplus/include)
include_directories(${THIRDPARTY}/boost/include)
#include_directories(${libsdsl_INCLUDE_DIRS})

link_directories(${THIRDPARTY}/libsdsl/lib)
link_directories(${THIRDPARTY}/dacs/lib)
link_directories(${THIRDPARTY}/asyncplusplus/lib)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # require at least gcc 4.8
  if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.7)
    message(FATAL_ERROR "GCC version must be at least 4.7!")
  endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  # require at least clang 3.4
  if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.4)
    message(FATAL_ERROR "Clang version must be at least 3.4!")
  endif()
else()
  message(WARNING "You are using an unsupported compiler! Compilation has only been tested with Clang and GCC.")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ")#-Wall -Wconversion -Wsign-conversion")

add_subdirectory(tests)
add_subdirectory(src)
add_subdirectory(tools)

