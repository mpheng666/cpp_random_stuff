cmake_minimum_required(VERSION 3.5)
project(daytime_server)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(Boost REQUIRED)
find_package(Threads REQUIRED)
include_directories( include ${Boost_INCLUDE_DIRS} )

add_executable(daytime_sync_server sync_daytime_server.cpp)
target_link_libraries(daytime_sync_server ${Boost_LIBRARIES} PRIVATE Threads::Threads)

add_executable(daytime_sync_client sync_daytime_client.cpp)
target_link_libraries(daytime_sync_client ${Boost_LIBRARIES} PRIVATE Threads::Threads)