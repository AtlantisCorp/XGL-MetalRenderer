# !! File XGLMetalRenderer/CMakeLists.txt
# !! Author Luk2010
# !! Date 2021/07/08

if (APPLE)

message(STATUS "[Plugin] installing XGLMetalRenderer plugin...")

cmake_minimum_required(VERSION 3.20)
project(XGLMetalRenderer)

file(
    GLOB XGLMetalRendererSrc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.mm
)

add_library(XGLMetalRenderer SHARED ${XGLMetalRendererSrc})

find_library(COCOA_LIBRARY Cocoa REQUIRED)
find_library(METAL_LIBRARY Metal REQUIRED)
find_library(METALKIT_LIBRARY MetalKit REQUIRED)
find_library(METAL_PERFORMANCE_SHADERS_LIBRARY MetalPerformanceShaders REQUIRED)

target_link_libraries(
    XGLMetalRenderer
    PUBLIC
        ${COCOA_LIBRARY}
        ${METAL_LIBRARY}
        ${METALKIT_LIBRARY}
        ${METAL_PERFORMANCE_SHADERS_LIBRARY}
)

install(
    TARGETS XGLMetalRenderer 
    LIBRARY DESTINATION ${XGL_PLUGINS_BINDIR}
)

endif(APPLE)
