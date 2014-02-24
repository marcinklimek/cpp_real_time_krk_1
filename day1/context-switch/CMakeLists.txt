cmake_minimum_required(VERSION 2.8)

project(context-switch)

add_executable(context-switch ctx_switch.cpp )
target_link_libraries( ${PROJECT_NAME}  pthread rt )

install(TARGETS context-switch RUNTIME DESTINATION bin)
