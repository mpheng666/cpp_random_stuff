cmake_minimum_required(VERSION 3.5)
project(asio_socket)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

find_package(Boost REQUIRED)
include_directories( include ${Boost_INCLUDE_DIRS} )

add_executable(tcp_server_blocking src/tcp_echo_server_blocking.cpp)
target_include_directories(tcp_server_blocking PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
$<INSTALL_INTERFACE:include>)
target_link_libraries(tcp_server_blocking PRIVATE Threads::Threads)

add_executable(tcp_client_blocking src/tcp_echo_client_blocking.cpp)
target_include_directories(tcp_client_blocking PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
  target_link_libraries(tcp_client_blocking PRIVATE Threads::Threads)