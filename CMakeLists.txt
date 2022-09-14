cmake_minimum_required(VERSION 3.20)
set(project_name bn)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(${project_name} LANGUAGES CXX)

add_subdirectory(src)
add_executable(${project_name}app main.cpp)
target_link_libraries(${project_name}app  battry_notification)