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
#include <Papillon/utils/constants.hpp>

#include<limits>

namespace pmc {

  //============================================================================
  // Versioning
  const unsigned int VERSION_MAJOR = 0;
  const unsigned int VERSION_MINOR = 0;
  const unsigned int VERSION_PATCH = 1;
  const bool VERSION_DEVELOPMENT = true;
  const unsigned int COPYRIGHT_YEAR = 2020;
  const char VERSION_STRING[] = "0.0.1 (Developement)";

  //============================================================================
  // Mathematical and Physical Constants
  const double INF = std::numeric_limits<double>::max();
  const double PI = 3.14159265358979323846264338327950288;
  const double RAD_TO_DEG = 360. / (2. * PI);
  const double DEG_TO_RAD = (2. * PI) / 360.;
  const double C_CM_S = 2.99792458E8; // Speed of light in cm/s
  const double N_AVG = 0.6022140857; // Avogadro's Constant
  const double EV_TO_K = 1.160451812E4; // eV per Kelvin
  const double SEC_TO_SHAKE = 1.E8; // sec/sh
  const double SHAKE_TO_SEC = 1.E-8; // sh/sec
  const double K_BOLTZ_EV = 8.617333262145E-5; // Boltzmann's constant in eV
  const double MEV_TO_EV = 1.E6; // MeV / eV
  const double EV_TO_MEV = 1.E-6; // eV / MeV

  //============================================================================
  // Program Parameters
  const double SURFACE_COINCIDENT = 1E-12;

}