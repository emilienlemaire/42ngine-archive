cmake_minimum_required(VERSION 3.15)
project(42ngine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
set(CCACHE_SLOPPINESS pch_defines,time_macros)
set(HEADERS 42ngine.h src/Window.h src/VertexArray.h src/VertexBuffer.h src/Shader.h)
include(cotire)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    include_directories(/usr/local/include)
    add_compile_definitions(FT_PLATFORM_APPLE)
else()
    message(FATAL_ERROR "42ngine is only compatible with macOS as of today")
endif()

add_subdirectory(libs/imgui)
add_subdirectory(libs/CppLogger)

add_library(42ngine STATIC
        42ngine.h
        src/Window.cpp
        src/VertexArray.cpp
        src/VertexBuffer.cpp
        src/Shader.cpp
        src/IndexBuffer.cpp
        src/IndexBuffer.h
        src/Application.cpp
        src/Application.h
        src/Renderer.cpp
        src/Renderer.h
        src/Camera.cpp
        src/Camera.h
        src/BufferLayout.cpp
        src/BufferLayout.h src/Texture.cpp src/Texture.h)

set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )

find_path(GLEW_INCLUDE_DIR GL/glew.h)
find_package(GLEW 2.1.0 REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenCV REQUIRED)

target_include_directories(42ngine PUBLIC ${INCLUDE_DIRECTORIES} ${OPENGL_INCLUDE_DIR} libs)
target_link_libraries(42ngine glm imgui glfw GLEW::GLEW ${OPENCV_LIBS} ${OPENGL_gl_LIBRARY} CppLogger)

if(${CMAKE_SYSTEM_NAME} STREQUAL Darwin)
    install(TARGETS 42ngine DESTINATION lib)
    install(FILES ${HEADERS} DESTINATION include/42ngine)
endif()
cotire(42ngine)