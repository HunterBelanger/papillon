cmake_minimum_required(VERSION 3.9)
project(papillon-tests LANGUAGES CXX)

add_executable(test tests_main.cpp
  vector_tests.cpp
  direction_tests.cpp
  xplane_tests.cpp
  yplane_tests.cpp
  zplane_tests.cpp
  plane_tests.cpp
  xcylinder_tests.cpp
  ycylinder_tests.cpp
  zcylinder_tests.cpp
  sphere_tests.cpp
  ray_tests.cpp
  half_space_tests.cpp
  intersection_tests.cpp
  union_tests.cpp
  difference_tests.cpp
)
target_compile_features(test PRIVATE cxx_std_17)
target_link_libraries(test Papillon gtest)
