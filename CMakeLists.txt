cmake_minimum_required(VERSION 3.10)
project(blinn LANGUAGES CXX CUDA)
enable_language(CUDA)
set(CMAKE_CXX_COMPILER "/usr/bin/g++-6")
set(CMAKE_CXX_STANDARD 14)
set(CUDA_TOOLKIT_ROOT_DIR "/usr/local/cuda-9.0")


find_package(CUDA REQUIRED)

include_directories(src)

# define unit tests
find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
add_executable(UnitTests
    src/test.cpp
        src/Computation.cu src/Computation.cuh)
target_link_libraries(UnitTests
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      )
enable_testing()
ADD_TEST (basic_test UnitTests)



# define exec
#cuda_add_executable(blinn src/main.cu)

add_executable(blinn
        src/color.cu
        src/color.cuh
        src/dbg.h
        src/geometry.cpp
        src/geometry.h
        src/main.cu
        src/point.cpp
        src/ray.h
        src/ray.cpp
        src/point.h
        src/render.cpp
        src/render.h
        src/sphere.cpp
        src/sphere.h
        src/square.cpp
        src/square.h
        src/blobsys.cpp
        src/blobsys.h
        src/tracer.cu
        src/tracer.h
        src/config.cpp
        src/config.h
        src/scene.cpp
        src/scene.h
        src/Computation.cu
        src/Computation.cuh
        )
set_property(TARGET blinn PROPERTY CUDA_STANDARD 14)
