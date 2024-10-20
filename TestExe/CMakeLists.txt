cmake_minimum_required(VERSION 3.8)

add_executable(TestExe "main.cpp")

target_link_libraries(TestExe PRIVATE BookLib)

target_include_directories(TestExe PRIVATE ${BookLib_SOURCE_DIR}/inc)