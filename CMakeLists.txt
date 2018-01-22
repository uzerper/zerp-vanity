cmake_minimum_required(VERSION 2.6)
project(skizzle)

set (CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")

message(${CMAKE_CXX_FLAGS})

add_subdirectory(src)
add_subdirectory(test)
