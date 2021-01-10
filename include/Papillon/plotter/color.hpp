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
#ifndef PAPILLON_COLOR_H
#define PAPILLON_COLOR_H

#include <Papillon/utils/pmc_exception.hpp>

#include <cmath>

namespace pmc {

  class Color {
    public:
      Color(): R_(1.), G_(1.), B_(1.) {}
      Color(float r, float g, float b): R_(r), G_(g), B_(b) {
        if(R_ > 1. || R_ < 0. || G_ > 1. || G_ < 0. || B_ > 1. || B_ < 0.) {
          std::string mssg = "Color component not in interval [0, 1].";
          throw PMCException(mssg, __FILE__, __LINE__);
        }
      }
      ~Color() = default;

      float R() const {return R_;}
      float G() const {return G_;}
      float B() const {return B_;}

      Color& operator+=(const Color& other) {
        R_ = std::fmin(1., R_+other.R_);
        G_ = std::fmin(1., G_+other.G_);
        B_ = std::fmin(1., B_+other.B_);

        return *this;
      }

      Color& operator*=(const Color& other) {
        R_ *= other.R_;
        G_ *= other.G_;
        B_ *= other.B_;

        return *this;
      }

      Color& operator*=(double c) {
        if(c < 0.) {
          std::string mssg = "Color multiplied by negative value.";
          throw PMCException(mssg, __FILE__, __LINE__);
        }

        R_ = std::fmin(1., R_*c);
        G_ = std::fmin(1., G_*c);
        B_ = std::fmin(1., B_*c);

        return *this;
      }

      Color& operator/=(double c) {
        if(c < 0.) {
          std::string mssg = "Color divided by negative value.";
          throw PMCException(mssg, __FILE__, __LINE__);
        }

        return this->operator*=(1./c);
      }

    private:
      float R_, G_, B_;
  };

  using Pixel = Color;

  inline Color operator+(const Color& c1, const Color& c2) {
    Color c = c1;
    c += c2;
    return c;
  }

  inline Color operator*(const Color& c1, const Color& c2) {
    Color c = c1;
    c *= c2;
    return c;
  }

  inline Color operator*(const Color& c1, double d) {
    Color c = c1;
    c *= d;
    return c;
  }

  inline Color operator/(const Color& c1, double d) {
    Color c = c1;
    c /= d;
    return c;
  }

}

#endif