cmake_minimum_required(VERSION 3.1)
project(my_lib)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -o3")

# include_directories(include)

add_library(tools src/tools.cpp)
add_executable(main src/main.cpp)
target_link_libraries(main tools)