cmake_minimum_required(VERSION 3.10)
project(blinn)
set(CMAKE_CXX_COMPILER "/usr/bin/g++-6")
set(CMAKE_CXX_STANDARD 14)

find_package(OpenMP)


if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -DNDEBUG")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif ()
find_package(CUDA REQUIRED)


include_directories(src)

# define unit tests
find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
add_executable(UnitTests
    src/test.cpp
)
target_link_libraries(UnitTests
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      )
enable_testing()
ADD_TEST (basic_test UnitTests)


# define exec
cuda_add_executable(blinn
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
        src/blobsys.cpp
        src/blobsys.h
        src/tracer.cpp
        src/tracer.h
        src/config.cpp
        src/config.h
        src/scene.cpp
        src/scene.h)
