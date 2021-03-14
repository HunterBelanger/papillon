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
#include <Papillon/geometry/surfaces/zcylinder.hpp>
#include <Papillon/utils/constants.hpp>

#include<cmath>

namespace pmc {

  ZCylinder::ZCylinder(double x_, double y_, double r_, BoundaryType bound,
    uint32_t i_id): Surface(bound,i_id), x0(x_), y0(y_), R(r_) {}

  Surface::Side ZCylinder::sign(const Position& r, const Direction& u) const {
    double x = r.x() - x0;
    double y = r.y() - y0;
    double eval = y*y + x*x - R*R;
    if(eval > SURFACE_COINCIDENT) return Side::Positive;
    else if(eval < -SURFACE_COINCIDENT) return Side::Negative;
    else {
      if(u.dot(normal(r)) > 0.) return Side::Positive;
      else return Side::Negative;
    }
  }

  double ZCylinder::distance(const Position& r, const Direction& u, uint32_t on_surf) const {
    double a = u.y()*u.y() + u.x()*u.x();
    if(a == 0. || on_surf == id_) return INF;

    double x = r.x() - x0;
    double y = r.y() - y0;
    double k = y*u.y() + x*u.x();
    double c = y*y + x*x - R*R;
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

  Direction ZCylinder::normal(const Position& r) const {
    double x = r.x() - x0;
    double y = r.y() - y0;
    return {x,y,0.};
  }
}
