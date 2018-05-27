cmake_minimum_required(VERSION 3.10)
project(blinn)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -DNDEBUG")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif ()

include_directories(src)
include_directories(include)

add_executable(blinn
        src/basics/color.cpp
        src/basics/color.h
        src/utils/dbg.h
        src/basics/geometry.cpp
        src/basics/geometry.h
        src/main.cpp
        src/basics/point.cpp
        src/basics/point.h
        src/basics/ray.cpp
        src/basics/ray.h
        src/rendersys/render.cpp
        src/rendersys/render.h
        src/renderables/sphere.cpp
        src/renderables/sphere.h
        src/basics/square.cpp
        src/basics/square.h
        src/physics/blobsys.cpp
        src/physics/blobsys.h
        #src/test.cpp
        src/rendersys/tracer.cpp
        src/rendersys/tracer.h src/utils/config.cpp src/utils/config.h src/rendersys/scene.cpp src/rendersys/scene.h)
