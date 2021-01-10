cmake_minimum_required(VERSION 3.9)
project(glad LANGUAGES C)

add_library(glad STATIC src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(glad PRIVATE -W -Wall -Wextra)
set_property(TARGET glad PROPERTY POSITION_INDEPENDENT_CODE ON)
