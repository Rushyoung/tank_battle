cmake_minimum_required(VERSION 3.28)
project(tank_battle)

set(CMAKE_PREFIX_PATH "C:/Qt/6.7.1/mingw_64/lib/cmake")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
include_directories(${PROJECT_SOURCE_DIR}/libs/asio-1.30.2/include)
#include_directories(${PROJECT_SOURCE_DIR}/HiEasyX)
set(CMAKE_CXX_STANDARD 17)
add_definitions(-D_WIN32_WINNT=0x0601)
#file(GLOB_RECURSE HIEASYX_SRC "HiEasyX/*.cpp")
add_executable(tank_battle
#        mainwindow.ui
        src/base.cpp
        include/base.hpp
        include/net.hpp
        include/chanel.hpp
        main.cpp
        include/grap.hpp
        src/graph.cpp
        include/basetype.hpp
        src/net.cpp
        src/basetype.cpp
        src/ui.cpp
#        HiEasyX.h
#        ${HIEASYX_SRC}
)

if(WIN32)
    target_link_libraries(tank_battle wsock32 ws2_32)
endif()

target_link_libraries(tank_battle Qt6::Core Qt6::Gui Qt6::Widgets)

#target_link_libraries(tank_battle easyx msimg32 gdiplus gdi32 winmm)