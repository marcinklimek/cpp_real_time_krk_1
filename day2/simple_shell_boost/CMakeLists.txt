cmake_minimum_required(VERSION 2.8)

project(tokens)

add_executable(tokens main.cpp)
ADD_DEFINITIONS("-std=c++11")
install(TARGETS tokens RUNTIME DESTINATION bin)
