cmake_minimum_required(VERSION 2.8)
project(shared_vector)
add_executable(shared_vector main.cpp shm_semaphore.cpp shm_vector.cpp shm_queue.cpp )

install(TARGETS shared_vector RUNTIME DESTINATION bin)
add_definitions("-std=c++11 ")










