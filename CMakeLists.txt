cmake_minimum_required(VERSION 3.10)
project(blinn)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -DNDEBUG")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif ()

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
