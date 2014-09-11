cmake_minimum_required(VERSION 2.8.3)
project(streaming_demo_ps4eye)

find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})
if(OpenCV)
	message("OpenCV FOUND")
endif(OpenCV)

include_directories(${OpenCV_INCLUDE_DIRS})

link_libraries(${OpenCV_Libs})
add_executable(client_ps4eye src/client.cpp )

target_link_libraries(client_ps4eye ${OpenCV_INCLUDE_DIRS} ${OpenCV_LIBRARIES} )

