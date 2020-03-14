cmake_minimum_required(VERSION 3.15)
project(imgui)

set(CMAKE_CXX_STANDARD 14)

add_library(imgui STATIC
            imgui.cpp
            imgui.h
            imgui_demo.cpp
            imgui_draw.cpp
            imgui_widgets.cpp
            imgui_internal.h
            imconfig.h
            imstb_rectpack.h
            imstb_textedit.h
            imstb_truetype.h
            examples/imgui_impl_glfw.cpp
            examples/imgui_impl_glfw.h
            examples/imgui_impl_opengl3.cpp
            examples/imgui_impl_opengl3.h)

set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )

find_path(GLEW_INCLUDE_DIR GL/glew.h)
find_package(GLEW 2.1.0 REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(CppLogger REQUIRED)

target_include_directories(imgui PUBLIC ${OPENGL_INCLUDE_DIR} ${PROJECT_SOURCE_DIR})
target_link_libraries(imgui glfw GLEW::GLEW ${OPENGL_gl_LIBRARY})