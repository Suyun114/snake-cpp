cmake_minimum_required(VERSION 3.0)
project(snake LANGUAGES CXX)

set(SOURCES src/main.cpp src/utils.cpp)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(snake ${SOURCES})
target_link_libraries(snake ${CURSES_LIBRARIES})