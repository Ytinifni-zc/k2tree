file(GLOB_RECURSE K2TREE_SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cc ../include/*.h)

add_library(${K2TREE_NAME} STATIC ${K2TREE_SRC_FILES})
target_link_libraries(${K2TREE_NAME} dacs sdsl divsufsort divsufsort64 async++)
include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${THIRDPARTY}/libsdsl/include
        ${THIRDPARTY}/dacs/include
        ${THIRDPARTY}/asyncplusplus/include
        ${THIRDPARTY}/boost/include
)

#install(TARGETS ${K2TREE_NAME}
#  LIBRARY DESTINATION lib
#  COMPONENT libraries
#)
