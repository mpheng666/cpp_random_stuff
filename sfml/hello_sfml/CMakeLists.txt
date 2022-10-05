cmake_minimum_required(VERSION 3.10)

project(hello_sfml)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
# add_subdirectory("SFML")

add_executable(hello_sfml src/main.cpp)
target_link_libraries(hello_sfml sfml-graphics sfml-audio)