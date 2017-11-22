cmake_minimum_required(VERSION 2.8) 
set(PROJECT_NAME dacs)
project(${PROJECT_NAME})

file(GLOB source_file "include/basics.c" "include/bitrankw32int.c" "include/dacs.c" "include/*.h")
add_library(${PROJECT_NAME}  ${source_file})
#add_library(${PROJECT_NAME} SHARED ${source_file})
add_executable(dacs_test "include/test.c" ${source_file})

set(CMAKE_CXX_FLAGS -O9)
