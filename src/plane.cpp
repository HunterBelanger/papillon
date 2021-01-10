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
#include <Papillon/geometry/surfaces/plane.hpp>
#include <Papillon/utils/constants.hpp>

#include<cmath>

namespace pmc {
  
  Plane::Plane(double A_, double B_, double C_, double D_, BoundaryType bound, uint32_t i_id): Surface(bound,i_id), A(A_), B(B_), C(C_), D(D_) {}

  Side Plane::sign(const Position& r, const Direction& u) const {
    double eval = A*r.x() + B*r.y() + C*r.z() - D;
    if(eval > SURFACE_COINCIDENT) return Side::Positive;
    else if(eval < -SURFACE_COINCIDENT) return Side::Negative;
    else {
      if(u.dot(normal(r)) > 0.) return Side::Positive;
      else return Side::Negative;
    }
  }

  double Plane::distance(const Position& r, const Direction& u) const {
    double num = D - A*r.x() - B*r.y() - C*r.z();
    double denom = A*u.x() + B*u.y() + C*u.z();
    if(std::abs(num/denom) < SURFACE_COINCIDENT || denom == 0.) return INF;
    else if(num/denom < 0.) return INF;
    else return num/denom;
  }

  Direction Plane::normal(const Position& /*r*/) const {return {A, B, C};}

  Ray Plane::get_ray(const Position& r, const Direction& u, Side side) const {
    Side r_side = sign(r,u);
    Side P = Side::Positive;
    Side N = Side::Negative;

    if(r_side == side) {
      // Position is in region, interval is (0,d)
      double dist = distance(r,u);
      if(dist == INF) return {{0.,0,P},{dist,0,P}};
      else if(r_side == Side::Positive) return {{0.,0,P},{dist,id_,P}};
      return {{0.,0,P},{dist,id_,N}};
    } else {
      double diff = D - A*r.x() - B*r.y() - C*r.z();
      // Position is not in region, either never intersects, or (d,INF)
      if(A*u.x() + B*u.y() + C*u.z() == 0.
         || std::fabs(diff) < SURFACE_COINCIDENT) return {{}};
      else {
        if(r_side == Side::Positive) return {{distance(r,u),id_,P}, {INF,0,N}};
        return {{distance(r,u),id_,N}, {INF,0,P}};
      }
    }
  }

  void Plane::translate(const Vector& v) {
    D += A*v.x();
    D += B*v.y();
    D += C*v.z(); 
  }

  std::shared_ptr<Surface> Plane::clone() const {
    return std::make_shared<Plane>(A, B, C, D, boundary_, id_); 
  }
}