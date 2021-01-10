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
#ifndef PAPILLON_DIRECTION_H
#define PAPILLON_DIRECTION_H

#include <Papillon/utils/vector.hpp>
#include <Papillon/utils/constants.hpp>

namespace pmc {

  class Direction : public _vector_base_ {
    public:
      Direction(): _vector_base_(1., 0., 0.) {}
      Direction(_vector_base_ vbase): _vector_base_(vbase) {
        double n = this->norm(); 
        x_ /= n;
        y_ /= n;
        z_ /= n;
      }
      Direction(double x, double y, double z): _vector_base_(x,y,z) {
        double n = this->norm(); 
        x_ /= n;
        y_ /= n;
        z_ /= n;
      }
      Direction(double mu, double phi): _vector_base_() {
        // Must have mu in [-1, 1]
        if(mu < -1. || mu > 1.) {
          std::string mssg = "mu must be in range [-1, 1].";
          throw PMCException(mssg, __FILE__, __LINE__);
        }

        // Must have phi in [0, 2*pi]
        if(phi < 0. || phi > 2.*PI) {
          std::string mssg = "phi must be in range [0, 2PI].";
          throw PMCException(mssg, __FILE__, __LINE__);
        }

        x_ = std::sqrt(1. - mu*mu)*std::cos(phi);
        y_ = std::sqrt(1. - mu*mu)*std::sin(phi);
        z_ = mu;
      }
      ~Direction() = default;  

      using _vector_base_::operator[];
  };

  //============================================================================
  // Operators for Direction
  
  inline Vector operator*(const Direction& d, double c) {
    return Vector(d[0]*c, d[1]*c, d[2]*c); 
  }

  inline Vector operator*(double c, const Direction& d) {
    return Vector(d[0]*c, d[1]*c, d[2]*c); 
  }

  inline Vector operator/(const Direction& d, double c) {
    return Vector(d[0]/c, d[1]/c, d[2]/c);
  }

  inline Vector operator+(const Vector& v, const Direction& d) {
    return Vector(v[0]+d[0],v[1]+d[1],v[2]+d[2]); 
  }

  inline Vector operator+(const Direction& d, const Vector& v) {
    return v + d;
  }

  inline Vector operator-(const Vector& v, const Direction& d) {
    return Vector(v[0]-d[0],v[1]-d[1],v[2]-d[2]); 
  }

  inline Vector operator-(const Direction& d, const Vector& v) {
    return Vector(d[0]-v[0], d[1]-v[1], d[2]-v[2]);
  }

  inline Vector operator+(const Direction& v, const Direction& d) {
    return Vector(v[0]+d[0],v[1]+d[1],v[2]+d[2]); 
  }

  inline Vector operator-(const Direction& v, const Direction& d) {
    return Vector(v[0]-d[0],v[1]-d[1],v[2]-d[2]); 
  }

  inline std::ostream& operator<<(std::ostream& s, const Direction& d) {
    s << "<" << d[0] << "," << d[1] << "," << d[2] << ">"; 
    return s;
  }

}

#endif
