cmake_minimum_required(VERSION 3.10)
project(blinn)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

add_executable(blinn
        src/color.cpp
        src/color.h
        src/dbg.h
        src/geometry.cpp
        src/geometry.h
        src/main.cpp
        src/point.cpp
        src/point.h
        src/ray.cpp
        src/ray.h
        src/render.cpp
        src/render.h
        src/sphere.cpp
        src/sphere.h
        src/square.cpp
        src/square.h
        src/system.cpp
        src/system.h
        #src/test.cpp
        src/tracer.cpp
        src/tracer.h)
