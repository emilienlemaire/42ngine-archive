cmake_minimum_required(VERSION 3.15)
project(CppLogger)

set(CMAKE_CXX_STANDARD 14)

add_library(CppLogger STATIC src/Log.cpp)

add_executable(test test/basicTest.cpp)

target_include_directories(test PUBLIC src)
target_link_libraries(test CppLogger)
install(TARGETS CppLogger DESTINATION lib)
install(FILES src/Log.h DESTINATION include)