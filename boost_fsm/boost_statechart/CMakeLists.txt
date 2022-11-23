cmake_minimum_required(VERSION 3.16.3)
project(hello_statechart)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost COMPONENTS) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(hello_statechart src/hello_statechart.cpp) 
    target_link_libraries(hello_statechart ${Boost_LIBRARIES})
endif()
