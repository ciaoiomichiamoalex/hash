cmake_minimum_required(VERSION 4.0)
project(hash C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(hash src/main.c)
