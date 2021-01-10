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
#include <Papillon/geometry/surfaces/yplane.hpp>
#include <Papillon/utils/constants.hpp>

#include<cmath>

namespace pmc {
  
  YPlane::YPlane(double y, BoundaryType bound, uint32_t i_id): Surface(bound,i_id), y0(y) {}

  Side YPlane::sign(const Position& r, const Direction& u) const {
    if(r.y() - y0 > SURFACE_COINCIDENT) return Side::Positive;
    else if(r.y() - y0 < -SURFACE_COINCIDENT) return Side::Negative;
    else {
      if(u.dot(normal(r)) > 0.) return Side::Positive;
      else return Side::Negative;
    }
  }

  double YPlane::distance(const Position& r, const Direction& u) const {
    double diff = y0 - r.y();
    if(std::fabs(diff) < SURFACE_COINCIDENT || u.y() == 0.) return INF;
    else if(diff / u.y() < 0.) return INF;
    else return diff/u.y();
  }

  Direction YPlane::normal(const Position& /*r*/) const {return {0., 1., 0.};}

  Ray YPlane::get_ray(const Position& r, const Direction& u, Side side) const {
    // Get sign of position, this determines lower bound on interval
    Side r_side = sign(r,u);
    
    double d_min, d_max;
    Side P = Side::Positive;
    Side N = Side::Negative;

    if(r_side == side) {
      // If r is in the region, the segment begins at r, where d=0
      d_min = 0.;

      // If inside, use distance function to get upper bound
      d_max = distance(r, u);
      if(d_max == INF) return {{d_min,0,P},{d_max,0,P}};
      else if(r_side == Side::Positive) return {{d_min,0,P}, {d_max,id_,P}};
      return {{d_min,0,P}, {d_max,id_,N}};
    } else {
      // r is not inside region, so we need to get two intersections
      // one where ray enters region, and one where exits (if applicable)
      double diff = y0 - r.y();
      if(diff / u.y() < 0. || u.y() == 0.
        || (std::fabs(diff) < SURFACE_COINCIDENT && r_side != side))  {
        // Ray will never enter region, return empty ray
        return {{}};
      } else {
        // Get where ray will enter
        d_min = diff/u.y();

        // Get where ray will exit. For plane, it is only INF
        d_max = INF;

        if(r_side == Side::Positive) return {{d_min,id_,P}, {d_max,0,P}};
        return {{d_min,id_,N}, {d_max,0,P}};
      }
    }
  }

  void YPlane::translate(const Vector& v) {
    y0 += v.y();
  }

  std::shared_ptr<Surface> YPlane::clone() const {
    return std::make_shared<YPlane>(y0, boundary_, id_); 
  }
}