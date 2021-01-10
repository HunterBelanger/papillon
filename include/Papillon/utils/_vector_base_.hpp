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
#ifndef PAPILLON_VECTOR_BASE_H
#define PAPILLON_VECTOR_BASE_H

#include <Papillon/utils/pmc_exception.hpp>

#include <cmath>
#include <iostream>

namespace pmc {

  class _vector_base_ {
    public:
      _vector_base_(): x_(0.), y_(0.), z_(0.) {}
      _vector_base_(double x, double y, double z): x_(x), y_(y), z_(z) {}
      ~_vector_base_() = default;

      double x() const {return x_;}
      double y() const {return y_;}
      double z() const {return z_;}

      double norm() const {
        return std::sqrt(x_*x_ + y_*y_ + z_*z_); 
      }

      double dot(const _vector_base_& other) const {
        return x_*other.x_ + y_*other.y_ + z_*other.z_; 
      }

      _vector_base_ cross(const _vector_base_& other) const {
        double cx = y_*other.z_ - z_*other.y_;
        double cy = z_*other.x_ - x_*other.z_;
        double cz = x_*other.y_ - y_*other.x_;

        return _vector_base_(cx, cy, cz); 
      }

      const double& operator[](size_t i) const {
        switch(i) {
          case 0:
            return x_;
            break;
          case 1:
            return y_;
            break;
          case 2:
            return z_;
            break; 
          default:
            std::string mssg = "index of " + std::to_string(i);
            mssg += " out of range.";
            throw PMCException(mssg, __FILE__, __LINE__);
            break;
        } 
      }

    protected:
      friend class Transformation;
      double x_, y_, z_;
  };

  //============================================================================
  // Operators for _vector_base_
  
  inline double operator*(const _vector_base_& v1, const _vector_base_& v2) {
    return v1.x()*v2.x() + v1.y()*v2.y() + v1.z()*v2.z(); 
  }

  inline bool operator==(const _vector_base_& v1, const _vector_base_& v2) {
    if(v1[0] != v2[0]) return false;
    else if(v1[1] != v2[1]) return false;
    else if(v1[2] != v2[2]) return false;
    else return true; 
  }

  inline bool operator!=(const _vector_base_& v1, const _vector_base_& v2) {
    return !(v1 == v2);
  }

  inline std::ostream& operator<<(std::ostream& s, const _vector_base_& v) {
    s << "(" << v[0] << "," << v[1] << "," << v[2] << ")"; 
    return s;
  }

}

#endif
