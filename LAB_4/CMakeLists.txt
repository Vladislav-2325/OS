cmake_minimum_required(VERSION 3.10)
project(Lab_4)

set(CMAKE_CXX_STANDARD 11)

#add_library(process_library STATIC source/process.cpp)

add_executable(main LAB_4\temperature_log\temperature_logger.cpp)
#target_link_libraries(main PRIVATE process_library)

