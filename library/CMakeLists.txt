set(CMAKE_C_STANDARD 99)
cmake_minimum_required(VERSION 3.15)
project(string_library)
set(SOURCES string_library.c string_library.h)

add_library(string_library STATIC ${SOURCES})
add_library(string_library-shared SHARED ${SOURCES})
set_target_properties(string_library-shared PROPERTIES OUTPUT_NAME string_library)