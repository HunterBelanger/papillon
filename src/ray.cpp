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
#include <Papillon/geometry/ray.hpp>
#include <algorithm>

namespace pmc {

Ray::Ray(SurfaceCrossing s_in, SurfaceCrossing s_out)
    : segments_{{s_in, s_out}} {}

Ray::Ray(const std::vector<Segment>& segments) : segments_(segments) {}

//==============================================================================
// The get_intersection, get_union, and get_difference methods which follow are
// based on the seminal 1982 paper by Scott Roth on ray-tracing [1]. I am not
// yet aware of better (meaning faster or more efficient) algorithms to perform
// these computations. That being said, there may be much which could be done
// to improve these current implementations, and this should be looked at
// in the future.
//
// [1] S. D. Roth, “Ray casting for modeling solids,” Comput Vision Graph,
// vol. 18, no. 2, pp. 109–144, 1982, doi: 10.1016/0146-664x(82)90169-1. 
//==============================================================================
Ray Ray::get_intersection(const Ray& r) const {
  // Get merged points
  std::vector<SurfaceCrossing> points = merge_segments(segments_, r.segments_);

  // There must be points.size()-1 regions, as each segment always
  // has two points. We have an extra at end though to make sure
  // last segment is processed when combining points
  std::vector<bool> is_inside(points.size(), false);

  // Go through and check midpoint of each segment
  for (size_t i = 0; i < points.size() - 1; i++) {
    // Get midpoint of segment
    double x_mid = (points[i + 1].distance - points[i].distance) * 0.5 +
                   points[i].distance;

    // Do chech for both original segments
    bool in_first = inside_region(segments_, x_mid);
    bool in_second = inside_region(r.segments_, x_mid);

    // Do intersection
    if (in_first && in_second) is_inside[i] = true;
  }

  // Produce new array of segments
  std::vector<Segment> new_segments;

  // Go through all points
  double d_min = -1.;
  double d_max = -1.;
  uint32_t s_min = 0;
  uint32_t s_max = 0;
  Side sd_min = Side::Positive;
  Side sd_max = Side::Negative;
  for (size_t i = 0; i < points.size(); i++) {
    if (is_inside[i]) {
      if (d_min == -1.) {
        d_min = points[i].distance;
        s_min = points[i].surface;
        sd_min = points[i].side;
      }
    } else {
      if (d_min != -1. && d_max == -1.) {
        // Completed segment
        d_max = points[i].distance;
        s_max = points[i].surface;
        sd_max = points[i].side;
        // Append segment
        new_segments.push_back({{d_min, s_min, sd_min}, {d_max, s_max, sd_max}});
        d_min = -1.;
        d_max = -1.;
        s_min = 0;
        s_max = 0;
        sd_min = Side::Positive;
        sd_max = Side::Negative;
      }
    }
  }

  return {new_segments};
}

Ray Ray::get_union(const Ray& r) const {
  // Get merged points
  std::vector<SurfaceCrossing> points = merge_segments(segments_, r.segments_);

  // There must be points.size()-1 regions, as each segment always
  // has two points. We have an extra at end though to make sure
  // last segment is processed when combining points
  std::vector<bool> is_inside(points.size(), false);

  // Go through and check midpoint of each segment
  for (size_t i = 0; i < points.size() - 1; i++) {
    // Get midpoint of segment
    double x_mid = (points[i + 1].distance - points[i].distance) * 0.5 +
                   points[i].distance;

    // Do chech for both original segments
    bool in_first = inside_region(segments_, x_mid);
    bool in_second = inside_region(r.segments_, x_mid);

    // Do union
    if (in_first || in_second) is_inside[i] = true;
  }

  // Produce new array of segments
  std::vector<Segment> new_segments;

  // Go through all points
  double d_min = -1.;
  double d_max = -1.;
  uint32_t s_min = 0;
  uint32_t s_max = 0;
  Side sd_min = Side::Positive;
  Side sd_max = Side::Negative;
  for (size_t i = 0; i < points.size(); i++) {
    if (is_inside[i]) {
      if (d_min == -1.) {
        d_min = points[i].distance;
        s_min = points[i].surface;
        sd_min = points[i].side;
      }
    } else {
      if (d_min != -1. && d_max == -1.) {
        // Completed segment
        d_max = points[i].distance;
        s_max = points[i].surface;
        sd_max = points[i].side;
        // Append segment
        new_segments.push_back({{d_min, s_min, sd_min}, {d_max, s_max, sd_max}});
        d_min = -1.;
        d_max = -1.;
        s_min = 0;
        s_max = 0;
        sd_min = Side::Positive;
        sd_max = Side::Negative;
      }
    }
  }

  return {new_segments};
}

Ray Ray::get_difference(const Ray& r) const {
  // Get merged points
  std::vector<SurfaceCrossing> points = merge_segments(segments_, r.segments_);

  // There must be points.size()-1 regions, as each segment always
  // has two points. We have an extra at end though to make sure
  // last segment is processed when combining points
  std::vector<bool> is_inside(points.size(), false);

  // Go through and check midpoint of each segment
  for (size_t i = 0; i < points.size() - 1; i++) {
    // Get midpoint of segment
    double x_mid = (points[i + 1].distance - points[i].distance) * 0.5 +
                   points[i].distance;

    // Do chech for both original segments
    bool in_first = inside_region(segments_, x_mid);
    bool in_second = inside_region(r.segments_, x_mid);

    // Do difference
    if (in_first && in_second == false) is_inside[i] = true;
  }

  // Produce new array of segments
  std::vector<Segment> new_segments;

  // Go through all points
  double d_min = -1.;
  double d_max = -1.;
  uint32_t s_min = 0;
  uint32_t s_max = 0;
  Side sd_min = Side::Positive;
  Side sd_max = Side::Negative;
  for (size_t i = 0; i < points.size(); i++) {
    if (is_inside[i]) {
      if (d_min == -1.) {
        d_min = points[i].distance;
        s_min = points[i].surface;
        sd_min = points[i].side;
      }
    } else {
      if (d_min != -1. && d_max == -1.) {
        // Completed segment
        d_max = points[i].distance;
        s_max = points[i].surface;
        sd_max = points[i].side;
        // Append segment
        new_segments.push_back({{d_min, s_min, sd_min}, {d_max, s_max, sd_max}});
        d_min = -1.;
        d_max = -1.;
      }
    }
  }

  return {new_segments};
}

std::vector<SurfaceCrossing> Ray::merge_segments(
    const std::vector<Segment>& s1, const std::vector<Segment>& s2) const {
  // Initialize merge points vector
  std::vector<SurfaceCrossing> points;
  // Allocate max possible number of points
  points.reserve(s1.size() + s2.size());

  // Go through all segments and add bounds to the points
  for (const auto& seg : s1) {
    points.push_back(seg.first);
    points.push_back(seg.second);
  }
  for (const auto& seg : s2) {
    points.push_back(seg.first);
    points.push_back(seg.second);
  }

  // Sort points
  std::sort(points.begin(), points.end());

  // Remove duplicates
  std::vector<SurfaceCrossing>::iterator it =
      std::unique(points.begin(), points.end());
  points.resize(std::distance(points.begin(), it));

  return points;
}

bool Ray::inside_region(const std::vector<Segment>& s, double x) const {
  // Go through all segments
  for (const auto& seg : s) {
    if (seg.first.distance <= x && x <= seg.second.distance) return true;
  }
  return false;
}

}  // namespace pmc
