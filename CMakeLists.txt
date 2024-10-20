CMAKE_MINIMUM_REQUIRED(VERSION 3.21)
PROJECT(open_platform_test)

SET(CMAKE_CXX_STANDARD 17)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/project_bin_files")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/project_bin_files")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory ("BookLib")
add_subdirectory ("TestExe")

set_target_properties(BookLib PROPERTIES FOLDER "BookLib")
set_target_properties(TestExe PROPERTIES FOLDER "TestExe")