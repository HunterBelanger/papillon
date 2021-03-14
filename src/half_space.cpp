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
#include <Papillon/geometry/csg/half_space.hpp>

#include<cmath>

namespace pmc {

  HalfSpace::HalfSpace(std::shared_ptr<Surface> surface, Surface::Side side, uint32_t id): Volume(id), surface_(surface), side_(side) {}

  bool HalfSpace::is_inside(const Position& r, const Direction& u, 
      uint32_t on_surf, Surface::Side on_side) const {
    // Check if on_surf matches id
    if(on_surf == surface_->id()) {
      if(on_side == side_) return true;
      else return false;
    }
    
    // Get distance to surface
    double d_to_surf = surface_->distance(r, u, on_surf);

    // Check if on boundary or not
    if(std::fabs(d_to_surf) <= SURFACE_COINCIDENT) {
      // Do check with dot product
      Direction norm = surface_->normal(r);
      if((side_ == Surface::Side::Positive) && (u.dot(norm)>0)) return true;
      else return false;
    } else {
      // Do check with sign
      if(side_ == surface_->sign(r,u)) return true;
      else return false;
    }
  }

  Boundary HalfSpace::get_boundary(const Position& r, const Direction& u, uint32_t on_surf) const {
    Boundary bound;
    bound.surface_id = surface_->id();
    bound.current_side = surface_->sign(r, u);
    bound.distance = surface_->distance(r, u, on_surf);
    bound.boundary_type = surface_->boundary();
    return bound;
  }
}
