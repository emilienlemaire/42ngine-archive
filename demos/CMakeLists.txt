cmake_minimum_required(VERSION 3.15)
project(demos)

set(CMAKE_CXX_STANDARD 14)

add_executable(demos
        Sandbox.cpp)

set(INCLUDE_DIRECTORIES src includes libs /usr/local/Cellar/opencv@2/2.4.13.7_5/include)
set(OPENCV_LIBS /usr/local/Cellar/opencv@2/2.4.13.7_5/lib/libopencv_core.dylib
        /usr/local/Cellar/opencv@2/2.4.13.7_5/lib/libopencv_imgproc.dylib
        /usr/local/Cellar/opencv@2/2.4.13.7_5/lib/libopencv_highgui.dylib)

find_path(GLEW_INCLUDE_DIR GL/glew.h)
find_package(GLEW 2.1.0 REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenCV REQUIRED)

target_include_directories(demos PUBLIC .. ${INCLUDE_DIRECTORIES})
target_link_libraries(demos ../cmake-build-debug/lib42ngine.a)
