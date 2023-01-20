#
# Copyright (c) 2016-2017 Vinnie Falco (vinnie dot falco at gmail dot com)
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Official repository: https://github.com/boostorg/beast
#

# if (OPENSSL_FOUND)
#     GroupSources(include/boost/beast beast)
#     GroupSources(example/common common)
#     GroupSources(example/websocket/server/sync-ssl "/")

#     add_executable (websocket-server-sync-ssl
#         ${BOOST_BEAST_FILES}
#         ${PROJECT_SOURCE_DIR}/example/common/server_certificate.hpp
#         Jamfile
#         websocket_server_sync_ssl.cpp
#     )

#     set_property(TARGET websocket-server-sync-ssl PROPERTY FOLDER "example-websocket-server")

#     target_link_libraries (websocket-server-sync-ssl
#         OpenSSL::SSL OpenSSL::Crypto
#         lib-asio
#         lib-asio-ssl
#         lib-beast
#         )

# endif()

cmake_minimum_required(VERSION 3.5)
project(websocket-server-sync-ssl)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

find_package(Boost REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
include_directories( include ${Boost_INCLUDE_DIRS} )

add_executable(${PROJECT_NAME} 
websocket_server_sync_ssl.cpp
# ${PROJECT_SOURCE_DIR}/../../example/common/server_certificate.hpp
)
target_link_libraries(${PROJECT_NAME} 
${Boost_LIBRARIES} PRIVATE Threads::Threads
OpenSSL::SSL OpenSSL::Crypto
)
