cmake_minimum_required(VERSION 3.5)

project(TO_Lab09_Threads LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Threads)

add_executable(TO_Lab09_Threads main.cpp)

