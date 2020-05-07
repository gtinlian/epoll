cmake_minimum_required(VERSION 3.11)
project(untitled)

set(CMAKE_CXX_STANDARD 14)
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -march=native -O3 -pthread" )
add_executable(untitled main.cpp Epoll.cpp)