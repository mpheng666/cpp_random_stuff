cmake_minimum_required(VERSION 3.5)
project(beast_websocket)


if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

find_package(Boost REQUIRED)
find_package(Threads REQUIRED)
include_directories( include ${Boost_INCLUDE_DIRS} )

add_executable(${PROJECT_NAME} src/simple_http_client.cpp)
target_link_libraries(daytime_sync_server ${Boost_LIBRARIES} PRIVATE Threads::Threads)
