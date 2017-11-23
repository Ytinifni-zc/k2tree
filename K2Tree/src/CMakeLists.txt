file(GLOB_RECURSE K2TREE_SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cc ../include/*.h)

message(${K2TREE_SRC_FILES})
add_library(${K2TREE_NAME} ${K2TREE_SRC_FILES})
target_link_libraries(${K2TREE_NAME} dacs sdsl divsufsort divsufsort64)
include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/libsdsl/include
        ${PROJECT_SOURCE_DIR}/dacs/include
)

#install(TARGETS ${K2TREE_NAME}
#  LIBRARY DESTINATION lib
#  COMPONENT libraries
#)
