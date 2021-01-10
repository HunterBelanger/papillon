cmake_minimum_required(VERSION 3.9)
project(papillon
  #VERSION 0.0.1
  DESCRIPTION "A continuous energy, Monte Carlo, neutron transport code"
  LANGUAGES CXX
)

# Settings to ensure proper version of OpenGL is found. Not sure if necessary ??
cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)

#===============================================================================
# Options
option(PAPILLON_GO_FAST "Enable -O3 compiler optimizations" OFF)
option(PAPILLON_GO_FASTER "Enable -Ofast and -ffast-math compiler optimizations" OFF)
option(PAPILLON_TESTS "Build tests" OFF)

#===============================================================================
# Add directories for the navigator
add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/imgui)

#===============================================================================
# Papillon Library
include(sourcelist.cmake)
add_library(Papillon SHARED ${PAPILLON_SOURCE_FILES})

# Add public interface includes directory
target_include_directories(Papillon PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>${CMAKE_CURRENT_SOURCE_DIR}/include
)
# Private includes for GLFW
target_include_directories(Papillon PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include)

# Require C++17 standard
target_compile_features(Papillon PRIVATE cxx_std_17)

# Get compiler info
# TODO, for now, only support Clang or GNU

# Set compile options for library
target_compile_options(Papillon PRIVATE -W -Wall -Wextra -Wpedantic #-Weffc++ Turn off -Weffc++ due to ImGUI imcludes caussing warnings
                      )
target_compile_options(Papillon PRIVATE $<$<CONFIG:DEBUG>:-g>)
target_compile_options(Papillon PRIVATE $<$<CONFIG:RELEASE>:-O2>)
target_compile_options(Papillon PRIVATE $<$<BOOL:PAPILLON_GO_FAST>:-O3>)
target_compile_options(Papillon PRIVATE $<$<BOOL:PAPILLON_GO_FASTER>:-Ofast -ffast-math>)

# Set compile definitions for use of the GUI and ploting libs
target_compile_definitions(Papillon PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)
target_link_libraries(Papillon PRIVATE pmcglfw glad imgui)

#===============================================================================
# Papillon Executable
add_executable(papillon src/main.cpp)
target_compile_features(papillon PRIVATE cxx_std_17)
target_compile_options(papillon PRIVATE -W -Wall -Wextra -Wpedantic -Weffc++)
target_compile_options(papillon PRIVATE $<$<CONFIG:DEBUG>:-g>)
target_compile_options(papillon PRIVATE $<$<CONFIG:RELEASE>:-O2>)
target_compile_options(Papillon PRIVATE $<$<BOOL:PAPILLON_GO_FAST>:-O3>)
target_compile_options(papillon PRIVATE $<$<BOOL:PAPILLON_GO_FASTER>:-Ofast -ffast-math>)
target_link_libraries(papillon PUBLIC Papillon)

#===============================================================================
# Tests
if(PAPILLON_TESTS)
  add_subdirectory(tests)
endif()

#===============================================================================
# Install
install(TARGETS Papillon EXPORT Papillon DESTINATION lib)
install(EXPORT Papillon FILE Papillon-config.cmake DESTINATION share/cmake/papillon)
install(DIRECTORY include/Papillon DESTINATION include)

install(TARGETS papillon EXPORT papillon DESTINATION bin)
