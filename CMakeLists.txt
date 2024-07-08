cmake_minimum_required(VERSION 3.27)
project(Tanker)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/MP)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

set(ASIO_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)

#set the goal to windows 10 and later
add_compile_options(-DWINVER=0x0A00 -D_WIN32_WINNT=0x0A00)

#set include directory
include_directories(include)

#set source directory
file(GLOB SOURCES "src/*.cpp")

#find all of the hieasyx files
#set(EASYX_PATH "D:/code/module/hi_easyx")
#file(GLOB_RECURSE EASYX_FILES "${EASYX_PATH}/*.cpp")

# cancel the console startup logo
add_definitions(-D_NO_START_ANIMATION_)


#add executable with sources and main.c file
add_executable(Tanker ${SOURCES} main.cpp ${EASYX_FILES})

target_compile_options(Tanker PUBLIC -DASIO_STANDALONE)
#set(CMAKE_CXX_FLAGS -DASIO_STANDALONE)
target_include_directories(Tanker PUBLIC ${ASIO_INCLUDE})
target_link_libraries(Tanker PUBLIC wsock32 ws2_32 easyx msimg32 gdiplus gdi32 winmm)