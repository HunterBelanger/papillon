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
#ifndef PAPILLON_GEO_NODE_H
#define PAPILLON_GEO_NODE_H

#include <Papillon/geometry/csg/volume.hpp>
#include <deque>
#include <memory>
#include <string>

namespace pmc {

//============================================================================
// GeoNode
// Base class for all nodes which make up the geometry-tree.
class GeoNode {
 public:
  GeoNode(std::shared_ptr<Volume> v, const std::string& name);
  GeoNode(std::shared_ptr<Volume> v, Vector t, const std::string& name);
  GeoNode(GeoNode* p, std::shared_ptr<Volume> v, Vector t,
          const std::string& name);

  GeoNode(const GeoNode&) = delete;
  GeoNode(GeoNode&&) = delete;
  GeoNode& operator=(const GeoNode&) = delete;

  ~GeoNode() = default;

  // add_node
  GeoNode* add_node(std::shared_ptr<Volume> v, Vector t, std::string name);
  GeoNode* add_node(std::unique_ptr<GeoNode> node, Vector t);
  GeoNode* add_node(std::unique_ptr<GeoNode> node);

  // Cloning
  std::unique_ptr<GeoNode> clone() const;
  // TODO std::unique_ptr<GeoNode> clone_with_material() const; // For depletion

  // Setters (shouldn't need to be inlined)
  void set_parent(GeoNode* p);
  void set_translation(Vector t);
  void set_name(const std::string& name);

  // Getters (should be inlined for speed)
  GeoNode* parent() const { return parent_; }
  Vector translation() const { return translation_; }
  std::shared_ptr<Volume> volume() const { return volume_; }
  const std::string& name() const { return name_; }
  size_t nchildren() const { return children_.size(); }

  // This method takes coordinates from the nodes local frame, and then finds
  // the child node (should one exist), which contains the given coordinates.
  // This will likely become a virtual method in the future, for lattices.
  GeoNode* find_child_node(const Position& r_local, const Direction& u_local,
                           uint32_t on_surface, Side on_side) const {
    for (const auto& child : children_) {
      if (child->is_inside_parent_frame(r_local, u_local, on_surface, on_side)) {
        return child.get();
      }
    }
    return nullptr;
  }

  bool is_inside_parent_frame(const Position& r_parent, const Direction& u,
                               uint32_t on_surf, Side on_side) const {
    Position r_local = r_parent + translation_;
    return volume_->is_inside(r_local, u, on_surf, on_side);
  }

  bool is_inside_local_frame(const Position& r_local, const Direction& u,
                              uint32_t on_surf, Side on_side) const {
    return volume_->is_inside(r_local, u, on_surf, on_side);
  }

  SurfaceCrossing distance_to_boundary(const Position& r_local,
                                       const Direction& u) const {
    Ray ray = volume_->get_ray(r_local, u);
    if (ray.size() == 0)
      return {INF, 0, Side::Positive};
    else if (ray[0].first.distance > 0.)
      return ray[0].first;
    else
      return ray[0].second;
  }

  SurfaceCrossing distance_to_child_boundary(const Position& r_local, const Direction& u) const {
    SurfaceCrossing boundary{INF, 0, Side::Positive};

    for (const auto& child : children_) {
      Vector to_child = child->translation();
      Position r_child = r_local + to_child;
      SurfaceCrossing child_boundary =
          child->distance_to_boundary(r_child, u);
      if (child_boundary < boundary) boundary = child_boundary;
    }

    return boundary;
  }

 private:
  std::string name_;
  GeoNode* parent_;
  std::shared_ptr<Volume> volume_;
  Vector translation_;
  std::deque<std::unique_ptr<GeoNode>> children_;
};

}  // namespace pmc

#endif