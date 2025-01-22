cmake_minimum_required(VERSION 3.30)
project(smart_pointers)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "-static")

add_executable(smart_pointers main.cpp)
