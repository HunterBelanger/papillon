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
#include <Papillon/geometry/surfaces/ycylinder.hpp>
#include <Papillon/utils/constants.hpp>

#include<cmath>

namespace pmc {

  YCylinder::YCylinder(double x_, double z_, double r_, BoundaryType bound, uint32_t i_id): Surface(bound,i_id), x0(x_), z0(z_), R(r_) {}

  Side YCylinder::sign(const Position& r, const Direction& u) const {
    double x = r.x() - x0;
    double z = r.z() - z0;
    double eval = x*x + z*z - R*R;
    if(eval > SURFACE_COINCIDENT) return Side::Positive;
    else if(eval < -SURFACE_COINCIDENT) return Side::Negative;
    else {
      if(u.dot(normal(r)) > 0.) return Side::Positive;
      else return Side::Negative;
    }
  }

  double YCylinder::distance(const Position& r, const Direction& u) const {
    double a = u.x()*u.x() + u.z()*u.z();
    if(a == 0.) return INF;

    double x = r.x() - x0;
    double z = r.z() - z0;
    double k = x*u.x() + z*u.z();
    double c = x*x + z*z - R*R;
    double quad = k*k - a*c;

    if(quad < 0.) return INF;
    else if(std::abs(c) < SURFACE_COINCIDENT) {
      if(k >= 0.) return INF;
      else return (-k + std::sqrt(quad))/a;
    } else if(c < 0.) {
      return (-k + std::sqrt(quad))/a;
    } else {
      double d = (-k - std::sqrt(quad))/a;
      if(d < 0.) return INF;
      else return d;
    }
  }

  Direction YCylinder::normal(const Position& r) const {
    double x = r.x() - x0;
    double z = r.z() - z0;
    return {x,0.,z};
  }

  Ray YCylinder::get_ray(const Position& r, const Direction& u,
      Side side) const {
    double a = u.x()*u.x() + u.z()*u.z();
    double x = r.x() - x0;
    double z = r.z() - z0;
    double k = x*u.x() + z*u.z();
    double c = x*x + z*z - R*R;
    double quad = k*k - a*c;
    Side P = Side::Positive;
    Side N = Side::Negative;

    if(side == Side::Negative) {
      // Region is the inside of cylinder
      if(c < -SURFACE_COINCIDENT) {
        // Position is inside cylinder, which is also inside region.
        // Low bound must be 0, and upper is intersection or inf
        if(a == 0.) return {{0.,0,P}, {INF,0,P}};
        else return {{0.,0,P}, {(-k + std::sqrt(quad))/a,id_,N}};

      } else if(c > SURFACE_COINCIDENT) {
        // Position is outside cylinder, outside region.
        // Could have one region (two intersections),
        // or could have none.
        if(a == 0. || quad < 0.) {
          // No intersections
          return {{}};
        } else {
          // Two intersections, both are positive or both are negative
          if((-k - std::sqrt(quad))/a < 0.) return {{}};
          else return {{(-k - std::sqrt(quad))/a,id_,P}, {(-k + std::sqrt(quad))/a,id_,N}};
        }
      } else {
        // On surface 
        if(a == 0.) return {{0.,0,P}, {INF,0,P}};
        else if(k > 0.) return {{}};
        else return {{0.,0,P}, {-2.*k/a,id_,N}};
      }
    } else {
      // Region is outside cylinder
      if(c > SURFACE_COINCIDENT) {
        // Position is outsde cylinder in region.
        // Lower bound is 0. Upper boud is Inf, or intersection.
        // If intersection, there is a second region for passing through
        // the cylinder.
        if(a == 0. || quad < 0.) return {{0.,0,P}, {INF,0,P}};
        else {
          if((-k + std::sqrt(quad))/a < 0.) return {{0.,0,P}, {INF,0,P}};
          else {
            // Two regions must be determined, (0,d1), (d2,INF)
            return {{{{0.,0,P},{(-k-std::sqrt(quad))/a,id_,P}},
              {{(-k+std::sqrt(quad))/a,id_,N},{INF,0,P}}}};
          }
        }
      } else if(c < -SURFACE_COINCIDENT) {
        // Position is inside cylinder, outside region.
        // Could have one segment, or none.
        if(a == 0.) return {{}};
        else return {{(-k + std::sqrt(quad))/a,id_,N}, {INF,0,P}};
      } else {
        // On surface
        if(a == 0.) return {{}};
        else if(k > 0.) return {{0.,0,P}, {INF,0,P}};
        else return {{-2.*k/a,id_,N}, {INF,0,P}};
      }
    }
  }

  void YCylinder::translate(const Vector& v) {
    x0 += v.x();
    z0 += v.z();
  }

  std::shared_ptr<Surface> YCylinder::clone() const {
    return std::make_shared<YCylinder>(x0, z0, R, boundary_, id_); 
  }
}
