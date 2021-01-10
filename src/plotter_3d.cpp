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

#include <imgui.h>

#include <Papillon/plotter/plotter_3d.hpp>

#include <cmath>

namespace pmc {

Plotter3D::Plotter3D(Geometry* geom, uint32_t screen_w, uint32_t screen_h)
    : Plotter(geom, screen_w, screen_h),
      camera(screen_w, screen_h),
      camera_to_geom(),
      width(0),
      height(0),
      resolution_scale(0.25),
      need_to_redraw(true) {
  width = std::round(resolution_scale * static_cast<double>(display_w));
  height = std::round(resolution_scale * static_cast<double>(display_h));

  background = Color(0.114, 0.6, 0.953);

  data_.resize(display_w * display_h);

  for (auto& c : data_) {
    c = background;
  }
}

void Plotter3D::draw_frame(uint32_t w, uint32_t h) {
  // Check if screen dimensions changed
  if (h != display_h) {
    display_h = h;
    height = std::round(resolution_scale * static_cast<double>(display_h));
    camera.set_image_height(height);
    need_to_redraw = true;
  }
  
  if (w != display_w) {
    display_w = w;
    width = std::round(resolution_scale * static_cast<double>(display_w));
    camera.set_image_width(width);
    need_to_redraw = true;
  }

  // TODO check for changes to camera_to_geom

  // TODO check for changes to resolution_scale

  // TODO check for changes in FOV
  // camera->set_field_of_view_def(new_fov);

  // TODO Draw plotting menu
  ImGui::ShowDemoWindow();

  // TODO Check for need to redraw

  if (need_to_redraw) {
    // Resize the data_ for new texture size
    data_.resize(width*height, background);

    render();

    need_to_redraw = false;
  }
}

void Plotter3D::render() {
  for (uint32_t x = 0; x < width; x++) {
    // Gaurd is here only to avoid compiler warning without OpenMP.
    // Inner loop is parallelized over out-loop, to minimize cache misses
    // as the data_ vector is stored in row-major order.
#ifdef _OPENMP
    #pragma omp parallel for
#endif
    for (uint32_t y = 0; y < height; y++) {
      size_t i = width*y + x;
      data_[i] = get_pixel_color(x, y);
    }
  }

  new_texture_ = true;
}

Color Plotter3D::get_pixel_color(int x, int y) const {
  // Get Direction in Camera coordiantes from camera center (at origin) to pixel center
  Direction u = camera.pixel_direction_camera_space(x, y);

  return background;
}

}  // namespace pmc