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
#ifndef PAPILLON_CONSTANTS_H
#define PAPILLON_CONSTANTS_H

namespace pmc {

  //============================================================================
  // Versioning
  extern const unsigned int VERSION_MAJOR;
  extern const unsigned int VERSION_MINOR;
  extern const unsigned int VERSION_PATCH;
  extern const bool VERSION_DEVELOPMENT;
  extern const unsigned int COPYRIGHT_YEAR;
  extern const char VERSION_STRING[];

  //============================================================================
  // Mathematical and Physical Constants
  extern const double INF;
  extern const double PI;
  extern const double RAD_TO_DEG;
  extern const double DEG_TO_RAD;
  extern const double C_CM_S; // Speed of light in cm/s
  extern const double N_AVG; // Avogadro's Constant
  extern const double EV_TO_K; // eV per Kelvin
  extern const double SEC_TO_SHAKE; // sec/sh
  extern const double SHAKE_TO_SEC; // sh/sec
  extern const double K_BOLTZ_EV; // Boltzmann's constant in eV
  extern const double MEV_TO_EV; // MeV / eV
  extern const double EV_TO_MEV; // eV / MeV

  //============================================================================
  // Program Parameters
  extern const double SURFACE_COINCIDENT;

}

#endif
