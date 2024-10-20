cmake_minimum_required(VERSION 3.8)

project(BookLib)

file(GLOB BookLibFiles "${CMAKE_CURRENT_SOURCE_DIR}/*/*")

add_library(BookLib SHARED ${BookLibFiles})
target_include_directories(BookLib PUBLIC ${BookLib_SOURCE_DIR}/inc)