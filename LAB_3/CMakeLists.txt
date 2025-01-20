cmake_minimum_required(VERSION 3.20)
project(Lab_3)

set(CMAKE_CXX_STANDARD 20)

#ADD_LIBRARY(process_library STATIC LAB_3\my_process_manager\main.cpp)

add_executable(main LAB_3\my_process_manager\main.cpp)
#target_link_libraries(main PRIVATE process_library)
