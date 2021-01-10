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
#ifndef PAPILLON_CAMERA_H
#define PAPILLON_CAMERA_H

#include <Papillon/utils/direction.hpp>

namespace pmc {

class Camera {
 public:
  Camera(uint32_t width, uint32_t height, double fov = PI / 2.)
      : image_width_(width),
        image_height_(height),
        fov_(fov),
        aspect_ratio_(0.) {
    aspect_ratio_ =
        static_cast<double>(image_width_) / static_cast<double>(image_height_);
  }
  ~Camera() = default;

  //========================================================================
  // Getters and Setters
  void set_image_width(uint32_t w) {
    image_width_ = w;
    aspect_ratio_ = image_width_ / image_height_;
  }
  uint32_t image_width() const { return image_width_; }

  void set_image_height(uint32_t h) {
    image_height_ = h;
    aspect_ratio_ = image_width_ / image_height_;
  }
  uint32_t image_height() const { return image_height_; }

  void set_field_of_view_rad(double fov) { fov_ = fov; }
  double field_of_view_rad() const { return fov_; }

  void set_field_of_view_deg(double fov) { fov_ = DEG_TO_RAD*fov; }
  double field_of_view_deg() const { return fov_*RAD_TO_DEG; }

  double aspect_ratio() const { return aspect_ratio_; }

  //========================================================================
  // Pixel Querying
  Position pixel_center_camera_space(uint32_t x, uint32_t y) const {
    double pixelNDC_x =
        (static_cast<double>(x) + 0.5) / static_cast<double>(image_width_);
    double pixelNDC_y =
        (static_cast<double>(y) + 0.5) / static_cast<double>(image_height_);

    double tan_fov_2 = std::tan(fov_ / 2.);

    double pixelCamera_x = (2. * pixelNDC_x - 1.) * aspect_ratio_ * tan_fov_2;
    double pixelCamera_y = (1. - 2. * pixelNDC_y) * tan_fov_2;

    return {pixelCamera_x, pixelCamera_y, -1.};
  }

  Direction pixel_direction_camera_space(uint32_t x, uint32_t y) const {
    return pixel_center_camera_space(x, y);
  }

 private:
  uint32_t image_width_, image_height_;
  double fov_, aspect_ratio_;
};

}  // namespace pmc

#endif