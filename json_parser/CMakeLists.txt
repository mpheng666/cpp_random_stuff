cmake_minimum_required(VERSION 3.10)

project(hello_json)

# find_package(nlohmann_json 3.2.0 REQUIRED)

add_executable(hello_json src/main.cpp)
# target_link_libraries(hello_json PRIVATE nlohmann_json::nlohmann_json)