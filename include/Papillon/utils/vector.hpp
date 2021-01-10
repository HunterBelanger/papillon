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
#ifndef PAPILLON_VECTOR_H
#define PAPILLON_VECTOR_H

#include <Papillon/utils/_vector_base_.hpp>

namespace pmc {
  
  class Vector : public _vector_base_ {
    public:
      Vector(): _vector_base_() {}
      Vector(double x, double y, double z): _vector_base_(x,y,z) {}
      Vector(_vector_base_ vbase): _vector_base_(vbase) {}
      ~Vector() = default;

      using _vector_base_::operator[];
      
      double& operator[](size_t i) {
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

      Vector& operator*=(double c) {
        x_ *= c;
        y_ *= c;
        z_ *= c; 

        return *this;
      }

      Vector& operator/=(double c) {
        return *this *= (1./c); 
      }

      Vector& operator+=(const Vector& other) {
        x_ += other.x_;
        y_ += other.y_;
        z_ += other.z_; 

        return *this;
      }

      Vector& operator-=(const Vector& other) {
        x_ -= other.x_;
        y_ -= other.y_;
        z_ -= other.z_; 

        return *this;
      }
  };
  
  // Typedef for Position, as there is no real difference between a
  // vector and a position.
  using Position = Vector;

  //============================================================================
  // Operators for Vector
  
  inline Vector operator+(const Vector& v1, const Vector& v2) {
    Vector v(v1);

    return v += v2;
  }

  inline Vector operator-(const Vector& v1, const Vector& v2) {
    Vector v(v1);

    return v -= v2;
  }

  inline Vector operator*(const Vector& v1, double c) {
    Vector v(v1); 

    return v *= c;
  }

  inline Vector operator*(double c, const Vector& v1) {
    Vector v(v1); 

    return v *= c;
  }

  inline Vector operator/(const Vector& v1, double c) {
    Vector v(v1); 

    return v /= c;
  }

}

#endif
