cmake_minimum_required(VERSION 3.10)
project(ProccessManager)

set(CMAKE_CXX_STANDARD 11)

add_library(process_library STATIC LAB_2\Proccess Manager\process_manager.cpp)

add_executable(main LAB_2\Proccess Manager\main.cpp)
target_link_libraries(main PRIVATE process_library)
