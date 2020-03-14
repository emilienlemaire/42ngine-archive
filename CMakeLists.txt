cmake_minimum_required(VERSION 3.15)
project(42ngine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
set(CCACHE_SLOPPINESS pch_defines,time_macros)
set(HEADERS
        42ngine.h
        src/Core/Application.h
        src/Core/EntryPoint.h
        src/BufferLayout.h
        src/Camera.h
        src/CameraController.h
        src/Element.h
        src/IndexBuffer.h
        src/Renderer.h
        src/Shader.h
        src/Texture.h
        src/VertexArray.h
        src/VertexBuffer.h
        src/Window.h)
include(cotire)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    include_directories(/usr/local/include)
    add_compile_definitions(FTN_PLATFORM_APPLE)
else()
    message(FATAL_ERROR "42ngine is only compatible with macOS as of today")
endif()

add_subdirectory(libs/imgui)

add_library(42ngine STATIC
        src/Core/Application.cpp
        src/BufferLayout.cpp
        src/Camera.cpp
        src/CameraController.cpp
        src/IndexBuffer.cpp
        src/Renderer.cpp
        src/Shader.cpp
        src/Texture.cpp
        src/VertexArray.cpp
        src/VertexBuffer.cpp
        src/Window.cpp
        )

set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )

find_path(GLEW_INCLUDE_DIR GL/glew.h)
find_package(GLEW 2.1.0 REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenCV REQUIRED)
find_package(CppLogger REQUIRED)

target_include_directories(42ngine PUBLIC ${OPENGL_INCLUDE_DIR} libs)
target_include_directories(42ngine PRIVATE src)
target_link_libraries(42ngine glm imgui glfw GLEW::GLEW ${OPENCV_LIBS} ${OPENGL_gl_LIBRARY} ${CPPLOGGER_LIBRARY})

if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    install(TARGETS 42ngine DESTINATION lib)
    install(FILES ${HEADERS} DESTINATION include/42ngine)
endif()
cotire(42ngine)

add_executable(demos
        demos/Sandbox.cpp
        )

target_include_directories(demos PRIVATE include)
target_link_libraries(demos 42ngine)
