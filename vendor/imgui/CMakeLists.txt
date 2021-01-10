cmake_minimum_required(VERSION 3.9)
project(imgui LANGUAGES CXX)

set(IMGUI_SOURCE_FILES ${IMGUI_SOURCE_FILES}
  src/imgui.cpp
  src/imgui_draw.cpp
  src/imgui_stdlib.cpp
  src/imgui_widgets.cpp  
  src/imgui_demo.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCE_FILES})
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(imgui PUBLIC cxx_std_17)
target_compile_options(imgui PRIVATE -W -Wall -Wextra -Wpedantic)
set_property(TARGET imgui PROPERTY POSITION_INDEPENDENT_CODE ON)