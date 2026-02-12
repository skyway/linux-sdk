cmake_minimum_required(VERSION 3.10.2)

project("sfu")

enable_language(CXX)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++" CACHE STRING "clang++ compile" FORCE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sfu.out main.cpp example_room.cpp)
target_compile_definitions(sfu.out PRIVATE ${SKYWAY_LINUX_DEFINITIONS})
target_include_directories(sfu.out PRIVATE ${SKYWAY_LINUX_INCLUDES})
target_link_libraries(sfu.out ${SKYWAY_LINUX_LIBS})