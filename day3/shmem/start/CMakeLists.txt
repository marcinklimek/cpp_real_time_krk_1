project(shmem)

add_executable(shmem main.cpp)

install(TARGETS shmem RUNTIME DESTINATION bin)
