cmake_minimum_required(VERSION 3.5.0)
project(clox VERSION 0.1.0 LANGUAGES C CXX)

add_executable(clox src/chunk.cpp src/debug.cpp src/main.cpp src/value.cpp src/vm.cpp)
