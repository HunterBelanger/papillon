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
#ifndef PAPILLON_GEOMETRY_H
#define PAPILLON_GEOMETRY_H

#include <Papillon/geometry/geo_node.hpp>
#include <Papillon/geometry/surfaces/surface.hpp>
#include <unordered_map>

namespace pmc {

class Geometry {
 public:
  Geometry(std::unordered_map<uint32_t, std::shared_ptr<Surface>> surfs,
           std::unique_ptr<GeoNode> r);

  Geometry(std::unordered_map<uint32_t, std::shared_ptr<Surface>> surfs,
           std::unordered_map<uint32_t, std::shared_ptr<Volume>> vols,
           std::unique_ptr<GeoNode> r);

  ~Geometry() = default;

  const std::unique_ptr<GeoNode>& root() const { return root_; }

 private:
  friend class GeoNavigator;

  std::vector<std::shared_ptr<Surface>> boundary_conditions;
  std::unordered_map<uint32_t, std::shared_ptr<Surface>> surfaces;
  std::unordered_map<uint32_t, std::shared_ptr<Volume>> volumes;
  std::unique_ptr<GeoNode> root_;
};

}  // namespace pmc

#endif