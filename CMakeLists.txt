cmake_minimum_required(VERSION 3.25)
project(ecg_tree)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ecg_tree
        node.cpp
        node.h
        main.cpp)
