set(PAPILLON_SOURCE_FILES ${PAPILLON_SOURCE_FILES}
  #=====================================
  # DearImGui implementation files
  src/imgui_impl_glfw.cpp
  src/imgui_impl_opengl3.cpp
  # Plotting
  #src/plotter_3d.cpp
  #src/geo_plotter.cpp
  # Geometry
  #src/geo_node.cpp
  #src/geometry.cpp
  # CSG
  src/intersection.cpp
  src/difference.cpp
  src/union.cpp
  src/half_space.cpp
  # Surfaces
  src/sphere.cpp
  src/zcylinder.cpp
  src/ycylinder.cpp
  src/xcylinder.cpp
  src/plane.cpp
  src/zplane.cpp
  src/yplane.cpp
  src/xplane.cpp
  # Utils
  src/constants.cpp
  src/transformation.cpp
)
