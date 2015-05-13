cmake_minimum_required(VERSION 3.2)
project(RayTracing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/objects/intersect.cpp
    src/objects/intersect.h
    src/objects/object.cpp
    src/objects/object.h
    src/objects/sphere.cpp
    src/objects/sphere.h
    src/tracer/camera.cpp
    src/tracer/camera.h
    src/tracer/ray.cpp
    src/tracer/ray.h
    src/util/vector3.cpp
    src/util/vector3.h
    src/main.cpp)

add_executable(RayTracing ${SOURCE_FILES})