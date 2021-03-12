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
#include <Papillon/geometry/surfaces/sphere.hpp>
#include <Papillon/utils/constants.hpp>

#include<cmath>

namespace pmc {
  
  Sphere::Sphere(double x_, double y_, double z_, double r_, BoundaryType bound, uint32_t i_id): Surface(bound,i_id), x0(x_), y0(y_), z0(z_), R(r_) {}

  Side Sphere::sign(const Position& r, const Direction& u) const {
    double x = r.x() - x0;
    double y = r.y() - y0;
    double z = r.z() - z0;
    double eval = (x*x) + (y*y) + (z*z) - R*R;
    if(eval > SURFACE_COINCIDENT) return Side::Positive;
    else if(eval < -SURFACE_COINCIDENT) return Side::Negative;
    else {
      if(u.dot(normal(r)) > 0.) return Side::Positive;
      else return Side::Negative;
    }
  }

  double Sphere::distance(const Position& r, const Direction& u, uint32_t on_surf) const {
    double x = r.x() - x0;
    double y = r.y() - y0;
    double z = r.y() - z0;
    double k = x*u.x() + y*u.y() + z*u.z();
    double c = x*x + y*y + z*z - R*R;
    double quad = k*k - c;

    if(quad < 0. || on_surf == id_) {
      return INF;
    } else if(std::abs(c) < SURFACE_COINCIDENT) {
      // On surface
      if(k >= 0.) return INF;
      else return -k + std::sqrt(quad);
    } else if(c < 0.) {
      return -k + std::sqrt(quad);
    } else {
      double d = -k - std::sqrt(quad);
      if(d < 0.) return INF;
      else return d;
    }
  }

  Direction Sphere::normal(const Position& r) const {
    double x = r.x() - x0;
    double y = r.y() - y0;
    double z = r.z() - z0;
    return {x,y,z};
  }

  Ray Sphere::get_ray(const Position& r, const Direction& u, 
      Side side) const {
    double x = r.x() - x0;
    double y = r.y() - y0;
    double z = r.y() - z0;
    double k = x*u.x() + y*u.y() + z*u.z();
    double c = x*x + y*y + z*z - R*R;
    double quad = k*k - c;
    Side P = Side::Positive;
    Side N = Side::Negative;
    
    if(side == Side::Negative) {
      // Region is inside sphere
      if(c < -SURFACE_COINCIDENT) {
        // Position is inside region and sphere. One segment, (0,d)
        return {{0.,0,P}, {-k + std::sqrt(quad),id_,N}};
      } else if (c > SURFACE_COINCIDENT) {
        // Position outside sphere and region.
        // Could have no segments, or 1 segment
        if(quad < 0. || (-k + std::sqrt(quad))< 0.) return {{}};
        else return {{-k - std::sqrt(quad),id_,P}, {-k + std::sqrt(quad),id_,N}};
      } else {
        // Position is on surface of sphere 
        // if k > 0, we are pointing outwards, so no intersection
        if(k > 0.) return {{}};
        else {
        // k < 0., so we are pointing inwards, c = 0 remeber, so the intersection is then
        // going to be larger solution
        return {{0.,0,P}, {-2.*k,id_,N}};
        }
      }
    } else {
      // Region is outside sphere
      if(c < -SURFACE_COINCIDENT){
        // Position is inside
        return {{-k + std::sqrt(quad),id_,N}, {INF,0,P}};
      } else if(c > SURFACE_COINCIDENT) {
        // Could have (0,INF) or (0,b1)(b2,INF)
        if(quad < 0. || (-k + std::sqrt(quad))< 0.) {
          return {{0.,0,P}, {INF,0,P}};
        } else {
          // Two segments
         return {{{{0.,0,P},{-k - std::sqrt(quad),id_,P}}, {{-k + std::sqrt(quad),id_,N},{INF,0,P}}}};
        }
      } else {
        // r is on surface
        if(k > 0.) return {{0.,0,P}, {INF,0,P}};
        else {
          return {{-2.*k,id_,N} ,{INF,0,P}};  
        }
      }
    }
  }

  void Sphere::translate(const Vector& v) {
    x0 += v.x();
    y0 += v.y();
    z0 += v.z();
  }

  std::shared_ptr<Surface> Sphere::clone() const {
    return std::make_shared<Sphere>(x0, y0, z0, R, boundary_, id_); 
  }
}
