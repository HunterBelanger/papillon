/*
 * Copyright 2020, Hunter Belanger
 *
 * hunter.belanger@gmail.com
 *
 * Ce logiciel est régi par la licence CeCILL soumise au droit français et
 * respectant les principes de diffusion des logiciels libres. Vous pouvez
 * utiliser, modifier et/ou redistribuer ce programme sous les conditions
 * de la licence CeCILL telle que diffusée par le CEA, le CNRS et l'INRIA 
 * sur le site "http://www.cecill.info".
 *
 * En contrepartie de l'accessibilité au code source et des droits de copie,
 * de modification et de redistribution accordés par cette licence, il n'est
 * offert aux utilisateurs qu'une garantie limitée.  Pour les mêmes raisons,
 * seule une responsabilité restreinte pèse sur l'auteur du programme,  le
 * titulaire des droits patrimoniaux et les concédants successifs.
 *
 * A cet égard  l'attention de l'utilisateur est attirée sur les risques
 * associés au chargement,  à l'utilisation,  à la modification et/ou au
 * développement et à la reproduction du logiciel par l'utilisateur étant 
 * donné sa spécificité de logiciel libre, qui peut le rendre complexe à 
 * manipuler et qui le réserve donc à des développeurs et des professionnels
 * avertis possédant  des  connaissances  informatiques approfondies.  Les
 * utilisateurs sont donc invités à charger  et  tester  l'adéquation  du
 * logiciel à leurs besoins dans des conditions permettant d'assurer la
 * sécurité de leurs systèmes et ou de leurs données et, plus généralement, 
 * à l'utiliser et l'exploiter dans les mêmes conditions de sécurité. 
 *
 * Le fait que vous puissiez accéder à cet en-tête signifie que vous avez 
 * pris connaissance de la licence CeCILL, et que vous en avez accepté les
 * termes.
 *
 * */
#include <Papillon/plotter/geo_plotter.hpp>
#include <Papillon/plotter/plotter_3d.hpp>

#include <imgui.h>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Include this cpp for the font
#include "dejavu_sans_mono.cpp"

#include <cmath>
#include <cstdio>


namespace pmc {

  GeoPlotter::GeoPlotter(Geometry* geom): display_w(0), display_h(0), scale_w(1.), scale_h(1.), geometry(geom), plotter(nullptr) {
    plotter = std::make_unique<Plotter3D>(geometry, display_w, display_h);
  }

  int GeoPlotter::run() {
    //==========================================================================
    // GLFW / GLAD SETUP
    //--------------------------------------------------------------------------
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) return 1;

    // Decide GL+GLSL versions
#if __APPLE__
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(2560, 1440, "Papillon GeoPlotter", NULL, NULL);

    if (window == NULL) return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Get inital scale of window, and set scale callback
    glfwGetWindowContentScale(window, &scale_w, &scale_h);
    // TODO check scale in look each frame ? Could be annoying as can change font size on fly
    // TODO change font size based on scale
    
    // Set auto scale to monitor in case of being move to new monitor
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
    
      
    // Initialize GLAD OpenGL loader
    bool glad_error = gladLoadGL() == 0;
    if (glad_error)
    {
      std::fprintf(stderr, "Failed to initialize OpenGL loader!\n");
      return 1;
    }
    //==========================================================================
    
    //==========================================================================
    // IMGUI SETUP
    //--------------------------------------------------------------------------
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Calculate and load font-size based on scale
    int font_size = std::round(13.333*scale_h);
    io.Fonts->AddFontFromMemoryCompressedTTF(DejaVuSansMono_compressed_data,
                                             DejaVuSansMono_compressed_size, font_size);
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Our state
    ImVec4 clear_color = ImVec4(1.f, 1.f, 1.f, 1.00f);
    //==========================================================================
    
    //==========================================================================
    // Main Loop
    //--------------------------------------------------------------------------
    while (!glfwWindowShouldClose(window)) {
      // Poll and handle events (inputs, window resize, etc.)
      // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
      // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
      // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
      // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
      glfwPollEvents();

      // Start the Dear ImGui frame
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      //========================================================================
      // Rendering
      glfwGetFramebufferSize(window, &display_w, &display_h);
      plotter->draw_frame(display_w, display_h);
      ImGui::Render(); // This must come after plotter->draw_frame ! Not sure why...
      glViewport(0, 0, display_w, display_h);
      glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
      glClear(GL_COLOR_BUFFER_BIT); // don't think I need this

      // Only load texture to OpenGL if a new texture has been rendered
      if(plotter->new_texture()) {
        // TODO
        //glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, display_w, display_h, GL_RGB, GL_FLOAT, plotter->data());
        int texture_w = plotter->current_texture_width();
        int texture_h = plotter->current_texture_height();
        glDrawPixels(texture_w, texture_h, GL_RGB, GL_FLOAT, plotter->data());
        plotter->texture_loaded();
      }

      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      glfwSwapBuffers(window);
    }
    // End Main Loop
    //==========================================================================
    
    //==========================================================================
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // Delete texture on GPU
    glDeleteTextures(1, &rendererID);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
  } // End of run method

  void GeoPlotter::glfw_error_callback(int error, const char* description) {
    std::fprintf(stderr, "GLFW Error %d: %s\n", error, description);
  }

}