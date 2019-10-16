cmake_minimum_required(VERSION 3.15)
set(CMAKE_C_STANDARD 99)
project(examples C)

add_library(libstring_library SHARED IMPORTED)

#if(WIN32)
#    set_property(TARGET string_library PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/library/build/libstring_library.dll)
#else()
#    set_property(TARGET string_library PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/library/build/libstring_library.so)
#endif()

add_executable(examples examples.c ../library/string_library.h)
#add_executable(bzip2recover bzip2recover.c)

target_include_directories(examples PUBLIC ../library)
#target_include_directories(bzip2recover PUBLIC ../library)

TARGET_LINK_LIBRARIES(examples ${CMAKE_CURRENT_SOURCE_DIR}/library/build/libstring_library.dll)
#TARGET_LINK_LIBRARIES(bzip2recover ${CMAKE_CURRENT_SOURCE_DIR}/../library/build/libbzip2.dll)