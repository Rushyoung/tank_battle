cmake_minimum_required(VERSION 3.27)
project(Tanker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ASIO_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)
message(STATUS "ASIO_INCLUDE: ${ASIO_INCLUDE}")

#set include directory
include_directories(include)

#set source directory
file(GLOB SOURCES "src/*.c")

#add executable with sources and main.c file
add_executable(Tanker ${SOURCES} main.cpp)

target_compile_options(Tanker PUBLIC -DASIO_STANDALONE)
#set(CMAKE_CXX_FLAGS -DASIO_STANDALONE)
target_include_directories(Tanker PUBLIC ${ASIO_INCLUDE})
target_link_libraries(Tanker PUBLIC -lwsock32 -lws2_32)