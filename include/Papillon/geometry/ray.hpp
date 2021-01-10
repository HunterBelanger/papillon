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
#ifndef PAPILLON_RAY_H
#define PAPILLON_RAY_H

#include <cstdint>
#include <vector>

namespace pmc {

enum class Side: bool { Positive=true, Negative=false };

struct SurfaceCrossing {
  double distance;

  // surface is positive if the ray interescting the surface
  // CAME FROM its positive side, and negative if the opposite.
  uint32_t surface;
  Side side;

  bool operator==(const SurfaceCrossing& s2) const {
    return ((distance == s2.distance) && (surface == s2.surface));
  }

  bool operator<(const SurfaceCrossing& s2) const {
    return (distance < s2.distance);
  }
};

class Ray {
 public:
  // This could of course be done with std::pair, but using Segment is shorter,
  // and also conveys more information.
  struct Segment {
    SurfaceCrossing first, second;
  };

  Ray(SurfaceCrossing s_in, SurfaceCrossing s_out);
  Ray(const std::vector<Segment>& segments);
  ~Ray() = default;

  size_t size() const { return segments_.size(); }
  Segment& operator[](size_t i) { return segments_[i]; }
  const Segment& operator[](size_t i) const { return segments_[i]; }

  Ray get_intersection(const Ray& r) const;
  Ray get_union(const Ray& r) const;
  Ray get_difference(const Ray& r) const;

 private:
  std::vector<Segment> segments_;

  std::vector<SurfaceCrossing> merge_segments(
      const std::vector<Segment>& s1, const std::vector<Segment>& s2) const;
  bool inside_region(const std::vector<Segment>& s, double x) const;
};  // Ray

}  // namespace pmc

#endif
