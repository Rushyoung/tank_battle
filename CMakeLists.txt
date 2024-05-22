cmake_minimum_required(VERSION 3.28)
project(tank_battle)
include_directories(${PROJECT_SOURCE_DIR}/libs/asio-1.30.2/include)
set(CMAKE_CXX_STANDARD 17)
link_libraries(libeasyx.a)

add_executable(tank_battle main.cpp
        src/base.cpp
        include/base.hpp
        include/net.hpp
        src/net.cpp
        include/chanel.hpp)
if(WIN32)
    target_link_libraries(tank_battle wsock32 ws2_32)
endif()