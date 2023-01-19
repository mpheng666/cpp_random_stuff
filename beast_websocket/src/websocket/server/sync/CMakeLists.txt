#
# Copyright (c) 2016-2017 Vinnie Falco (vinnie dot falco at gmail dot com)
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Official repository: https://github.com/boostorg/beast
#

# GroupSources(include/boost/beast beast)
# GroupSources(example/websocket/server/sync "/")

# add_executable (websocket-server-sync
#     ${BOOST_BEAST_FILES}
#     Jamfile
#     websocket_server_sync.cpp
# )

# target_link_libraries(websocket-server-sync
#     lib-asio
#     lib-beast)

# set_property(TARGET websocket-server-sync PROPERTY FOLDER "example-websocket-server")

cmake_minimum_required(VERSION 3.5)
project(websocket-server-sync)

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

add_executable(${PROJECT_NAME} websocket_server_sync.cpp)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} PRIVATE Threads::Threads)


