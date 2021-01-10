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
#ifndef PAPILLON_TRANSFORMATION_H
#define PAPILLON_TRANSFORMATION_H

#include <Papillon/utils/direction.hpp>

#include <array>

namespace pmc {

  class Transformation {
    public:
      Transformation();
      ~Transformation() = default;

      static Transformation translation(double x, double y, double z);
      static Transformation translation(_vector_base_ v);
      static Transformation rotation_x(double theta);
      static Transformation rotation_y(double theta);
      static Transformation rotation_z(double theta);
      static Transformation scale(double s);
      static Transformation scale_x(double s);
      static Transformation scale_y(double s);
      static Transformation scale_z(double s);

      std::array<double,4>& operator[](size_t i) {return data_[i];}
      const std::array<double,4>& operator[](size_t i) const {return data_[i];}

      Transformation inverse() const {
        double a = data_[0][0]; double b = data_[0][1]; double c = data_[0][2];
        double d = data_[1][0]; double e = data_[1][1]; double f = data_[1][2];
        double g = data_[2][0]; double h = data_[2][1]; double i = data_[2][2];

        double A = e*i - f*h; double B = -(d*i - f*g); double C = d*h - e*g;
        double D = -(b*i - c*h); double E = a*i - c*g; double F = -(a*h - b*g);
        double G = b*f - c*e; double H = -(a*f - c*d); double I = a*e - b*d;

        // Calculate determinant of the 3x3 matrix in upper left
        double det = a*A + b*B + c*C;

        Transformation out;
        // Construct inverse of 3x3 matrix in upper left
        out[0][0] = (1./det)*A; out[0][1] = (1./det)*D; out[0][2] = (1./det)*G;
        out[1][0] = (1./det)*B; out[1][1] = (1./det)*E; out[1][2] = (1./det)*H; 
        out[2][0] = (1./det)*C; out[2][1] = (1./det)*F; out[2][2] = (1./det)*I;

        // Inverse portion for translation vector.
        //Uses previously defined inverse.
        out[0][3] = -(out[0][0]*data_[0][3]+out[0][1]*data_[1][3]+out[0][2]*data_[2][3]);
        out[1][3] = -(out[1][0]*data_[0][3]+out[1][1]*data_[1][3]+out[1][2]*data_[2][3]);
        out[2][3] = -(out[2][0]*data_[0][3]+out[2][1]*data_[1][3]+out[2][2]*data_[2][3]);

        return out;
      }

    private:
      std::array<std::array<double,4>,3> data_;
  };

  inline Vector operator*(const Transformation& T, const Vector& v) {
    double x = T[0][0]*v.x() + T[0][1]*v.y() + T[0][2]*v.z() + T[0][3];
    double y = T[1][0]*v.x() + T[1][1]*v.y() + T[1][2]*v.z() + T[1][3];
    double z = T[2][0]*v.x() + T[2][1]*v.y() + T[2][2]*v.z() + T[2][3];

    return Vector(x,y,z);
  }

  inline Direction operator*(const Transformation& T, const Direction& v) {
    double x = T[0][0]*v.x() + T[0][1]*v.y() + T[0][2]*v.z();
    double y = T[1][0]*v.x() + T[1][1]*v.y() + T[1][2]*v.z();
    double z = T[2][0]*v.x() + T[2][1]*v.y() + T[2][2]*v.z();

    return Direction(x,y,z);
  }

  inline Transformation operator*(const Transformation& A, const Transformation& B) {
    Transformation out;

    // Zero diagonals
    for(size_t i = 0; i < 3; i++) out[i][i] = 0.;

    // Do multiplication
    for(size_t i = 0; i < 3; i++) {
      for(size_t j = 0; j < 4; j++) {
        for(size_t k = 0; k < 3; k++) {
          out[i][j] += A[i][k]*B[k][j];
        }
        if(j == 3) out[i][j] += A[i][j];
      }
    }

    return out;
  }

}

#endif