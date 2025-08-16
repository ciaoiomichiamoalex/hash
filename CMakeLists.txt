cmake_minimum_required(VERSION 4.0)
project(hash C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_library(hash STATIC src/hash.c)

add_executable(main src/main.c)

target_link_libraries(main PRIVATE hash)
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/src)
