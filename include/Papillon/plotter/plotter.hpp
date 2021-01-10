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
#ifndef PAPILLON_PLOTTER_H
#define PAPILLON_PLOTTER_H

#include <Papillon/geometry/geometry.hpp>
#include <Papillon/plotter/color.hpp>

#include <vector>

namespace pmc {

  class Plotter {
    public:
      Plotter(Geometry* geom, uint32_t w, uint32_t h):geometry(geom), display_w(w), display_h(h), background(), new_texture_(true), data_() {}
      Plotter(const Plotter&) = delete;
      Plotter& operator=(const Plotter&) = delete;
      virtual ~Plotter() = default;

      virtual void draw_frame(uint32_t w, uint32_t h) = 0;
      virtual uint32_t current_texture_width() const = 0;
      virtual uint32_t current_texture_height() const = 0;
      
      const Color* data() {return data_.data();}

      bool new_texture() const {return new_texture_;}
      void texture_loaded() {new_texture_ = false;}

      uint32_t current_display_width() const {return display_w;}
      uint32_t current_display_height() const {return display_h;}

    protected:
      Geometry* geometry;
      uint32_t display_w, display_h;
      Color background;
      bool new_texture_;
      std::vector<Color> data_;

  };

}

#endif