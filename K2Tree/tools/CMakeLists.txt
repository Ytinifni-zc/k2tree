include_directories(${CMAKE_SOURCE_DIR}/tools)

set(TOOLS_DIR ${PROJECT_SOURCE_DIR}/tools)
file(GLOB TOOLS_SRCS RELATIVE ${TOOLS_DIR} "*.cc")
foreach(tool ${TOOLS_SRCS})
    get_filename_component(TOOL_NAME ${tool} NAME_WE)
    add_executable(${TOOL_NAME} ${TOOLS_DIR}/${tool})
    set_target_properties(${TOOL_NAME}
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${BUILD_DIR}/tools"
            )

    target_link_libraries(${TOOL_NAME} ${K2TREE_NAME} dacs sdsl divsufsort divsufsort64)
endforeach()