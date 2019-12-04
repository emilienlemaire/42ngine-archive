cmake_minimum_required(VERSION 3.15)
project(42ngine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
set(CCACHE_SLOPPINESS pch_defines,time_macros)
include(cotire)

include_directories(libs)

add_subdirectory(libs/CppLogger)

add_library(42ngine SHARED
        src/Window.cpp
        src/Window.h)

set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )

find_path(GLEW_INCLUDE_DIR GL/glew.h)
find_package(GLEW 2.1.0 REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_library(CppLogger REQUIRED)

target_include_directories(42ngine PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(42ngine CppLogger glfw GLEW::GLEW ${OPENGL_gl_LIBRARY} ${OpenCV_LIBS})

install(TARGETS 42ngine DESTINATION lib)
install(FILES 42ngine.h DESTINATION include)
cotire(42ngine)