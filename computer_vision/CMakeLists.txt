cmake_minimum_required(VERSION 3.0.2) 
PROJECT (edge_detector)
find_package(OpenCV REQUIRED )

add_executable( edge_detector src/edge_canny.cpp  )
target_link_libraries( edge_detector ${OpenCV_LIBS} )