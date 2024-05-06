cmake_minimum_required(VERSION 3.28)
project(tank_battle)

set(CMAKE_CXX_STANDARD 20)
link_libraries(libeasyx.a)
add_executable(tank_battle main.cpp)
