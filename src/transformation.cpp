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

#include <Papillon/utils/transformation.hpp>

#include <cmath>

namespace pmc {

  Transformation::Transformation() {
    data_ = {1., 0., 0., 0.,
             0., 1., 0., 0.,
             0., 0., 1., 0.};
  }

  Transformation Transformation::translation(double x, double y, double z) {
    Transformation out;

    out.data_ = {1., 0., 0., x,
                 0., 1., 0., y,
                 0., 0., 1., z};

    return out;
  }

  Transformation Transformation::translation(_vector_base_ v) {
    Transformation out;
    
    out.data_ = {1., 0., 0., v.x(),
                 0., 1., 0., v.y(),
                 0., 0., 1., v.z()};

    return out;
  }

  Transformation Transformation::rotation_x(double theta) {
    Transformation out;
    double c = std::cos(theta);
    double s = std::sin(theta);

    out.data_ = {1., 0., 0., 0.,
                 0., c , -s, 0.,
                 0., s ,  c, 0.};

    return out;
  }

  Transformation Transformation::rotation_y(double theta) {
    Transformation out;
    double c = std::cos(theta);
    double s = std::sin(theta);

    out.data_ = {c , 0., s , 0.,
                 0., 1 , 0., 0.,
                 -s, 0., c , 0.};

    return out;
  }

  Transformation Transformation::rotation_z(double theta) {
    Transformation out;

    double c = std::cos(theta);
    double s = std::sin(theta);

    out.data_ = {c ,-s , 0., 0.,
                 s , c , 0., 0.,
                 0., 0., 1., 0.};

    return out;
  }

  Transformation Transformation::scale(double s) {
    Transformation out;

    out.data_ = {s , 0., 0., 0.,
                 0., s , 0., 0.,
                 0., 0., s , 0.};

    return out;
  }

  Transformation Transformation::scale_x(double s) {
    Transformation out;

    out.data_ = {s , 0., 0., 0.,
                 0., 1., 0., 0.,
                 0., 0., 1., 0.};

    return out;
  }

  Transformation Transformation::scale_y(double s) {
    Transformation out;

    out.data_ = {1., 0., 0., 0.,
                 0., s , 0., 0.,
                 0., 0., 1., 0.};

    return out;
  }

  Transformation Transformation::scale_z(double s) {
    Transformation out;

    out.data_ = {0., 0., 0., 0.,
                 0., 1., 0., 0.,
                 0., 0., s , 0.};

    return out;
  }

}