cmake_minimum_required(VERSION 3.10.2)

project("opencv")

enable_language(CXX)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++" CACHE STRING "clang++ compile" FORCE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(opencv.out main.cpp example_room.cpp)
target_compile_definitions(opencv.out PRIVATE ${SKYWAY_LINUX_DEFINITIONS})
target_include_directories(opencv.out PRIVATE ${SKYWAY_LINUX_INCLUDES})
target_link_libraries(opencv.out ${SKYWAY_LINUX_LIBS})
