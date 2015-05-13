cmake_minimum_required(VERSION 2.6)

project(RayTracing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

AUX_SOURCE_DIRECTORY(src DIR_SRCS)

add_executable(RayTracing ${DIR_SRCS})
