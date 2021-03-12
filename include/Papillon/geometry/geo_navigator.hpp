/*
 * Copyright 2021, Hunter Belanger
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
#ifndef PAPILLON_GEO_NAVIGATOR_H
#define PAPILLON_GEO_NAVIGATOR_H

#include <Papillon/geometry/geometry.hpp>

namespace pmc {

struct Boundary {
  double distance;
  std::shared_ptr<Surface> surface;
  Side side;
};

class GeoNavigator {
 public:
  GeoNavigator(Geometry* geom, Position r_global, Direction u_global)
      : geometry(geom),
        current_node_(geom->root().get()),
        r_local_(r_global),
        u_local_(u_global),
        global_to_local(),
        on_surface(0),
        on_side(Side::Positive),
        next_boundary_{INF, nullptr, Side::Positive},
        lost(false) {
    find_location_from_current();
  }
  GeoNavigator(const GeoNavigator& other)
      : geometry(other.geometry),
        current_node_(other.current_node_),
        r_local_(other.r_local_),
        u_local_(other.u_local_),
        global_to_local(other.global_to_local),
        on_surface(other.on_surface),
        on_side(other.on_side),
        next_boundary_(other.next_boundary_),
        lost(other.lost) {}
  GeoNavigator& operator=(const GeoNavigator& other) {
    geometry = other.geometry;
    current_node_ = other.current_node_;
    r_local_ = other.r_local_;
    u_local_ = other.u_local_;
    global_to_local = other.global_to_local;
    on_surface = other.on_surface;
    on_side = other.on_side;
    next_boundary_ = other.next_boundary_;
    lost = other.lost;
    return *this;
  }
  ~GeoNavigator() = default;

  GeoNode* current_node() const { return current_node_; }
  Position r_local() const { return r_local_; }
  Direction u_local() const { return u_local_; }
  bool is_lost() const { return lost; }

  void find_location_from_root(Position r_global, Direction u_global) {
    // Set current node to root, and reset quantities
    current_node_ = geometry->root().get();
    r_local_ = r_global;
    u_local_ = u_global;
    global_to_local = Vector(0., 0., 0.);
    lost = false;
    find_location_from_current();
  }

  // This function starts from the current node, and moves up/down the tree
  // untill it has found the deepest node which contains the current location.
  // If the current location is not found, the position must be outisde of the
  // geometry, in which case thee current_node_ is set to the root of the
  // geometry, to allow for use in the plotting functionality.
  void find_location_from_current() {
    bool found_end_node = false;
    while (!found_end_node) {
      // First check to see if we are inside the current node
      if (current_node_->is_inside_local_frame(r_local_, u_local_,
                                                on_surface, on_side)) {
        // We are inside the current node. This means we can keep moving
        // down the tree into children, until the current node has no
        // more children, in which case we are as far in as possible.
        while (current_node_->nchildren() > 0) {
          GeoNode* child =
              current_node_->find_child_node(r_local_, u_local_, on_surface, on_side);
          if (child) {
            current_node_ = child;
            Transformation parent_to_child = child->transformation();
            global_to_local = parent_to_child * global_to_local;
            r_local_ = parent_to_child * r_local_;
          } else
            break;
        }
        lost = false;
        found_end_node = true;
      } else {
        while (!current_node_->is_inside_local_frame(r_local_, u_local_,
                                                      on_surface, on_side)) {
          // We must go up a node, and see if we are inside it
          if (current_node_->parent()) {
            current_node_ = current_node_->parent();
            Transformation current_to_previous = current_node_->transformation().inverse();
            global_to_local = current_to_previous * global_to_local;
            r_local_ = current_to_previous * r_local_;
          } else {
            // There is no parent node, so the particle is forever lost
            lost = true;
            found_end_node = true;  // Just to get out of outer loop
            current_node_ = geometry->root().get();
            break;
          }
        }  // While not in current node
      }    // If not in current node
    }      // While not found_end_node
  }

  // This method checks to see if the current coordinates are located inside
  // of the current node.
  bool is_inside_current() const {
    return current_node_->is_inside_local_frame(r_local_, u_local_,
                                                 on_surface, on_side);
  }

  void move_distance(double d) {
    r_local_ += d * u_local_;

    // If we were on a surface, but moved, we no longer are, so we
    // can set it back to zero
    if (on_surface != 0) on_surface = 0;
  }

  void set_direction(const Direction& u) { 
    u_local_ = u; 
  }

  void set_new_global_coords(Position r_global, Direction u_global) {
    r_local_ = r_global + global_to_local;
    u_local_ = u_global;
  }

  void set_on_surface(uint32_t on_surf, Side on_sd) {
    on_surface = on_surf;
    on_side = on_sd;
  }

  Boundary find_next_boundary() {
    // Get intersection with current node volume first
    SurfaceCrossing boundary = current_node_->distance_to_boundary(r_local_, u_local_);

    // Now must check boundary to nearest child
    SurfaceCrossing child_boundary = current_node_->distance_to_child_boundary(r_local_, u_local_);

    if(child_boundary < boundary) boundary = child_boundary;
    

    uint32_t surf_id = boundary.surface;
    std::shared_ptr<Surface> surface = nullptr;
    if (surf_id != 0 && geometry->surfaces.find(surf_id) == geometry->surfaces.end()) {
      // Cann't find surface
      std::string mssg = "Cannot find surface with id " + std::to_string(surf_id) + ".";
      throw PMCException(mssg, __FILE__, __LINE__);
    } else if (surf_id != 0) {
      surface = geometry->surfaces[surf_id];
    }

    next_boundary_ = {boundary.distance, surface, boundary.side};

    return next_boundary_;
  }

  // TODO Boundary find_next_surface() const {}

  Boundary next_boundary() const {
    return next_boundary_;
  }

  void reflect_with_next_boundary() {
    // Only try to reflect if there is a true boundary (i.e. a surface),
    // and not just an "infinity" boundary.
    if(next_boundary_.surface) {
      // Travel distance to surface
      r_local_ += next_boundary_.distance * u_local_;

      // Set on_surface
      on_surface = next_boundary_.surface->id();
      
      // Set on_side to same side as we were just on
      on_side = next_boundary_.side;

      // Change direction
      Direction n = next_boundary_.surface->normal(r_local_);
      u_local_ = u_local_ - 2.*(u_local_*n)*n;
    }
  }

  void cross_next_boundary() {
    // Only try to cross if there is a true boundary (i.e. a surface), and
    // not just an "infinity" boundary.
    if(next_boundary_.surface) {
      // Travel distance to surface
      r_local_ += next_boundary_.distance * u_local_;

      // Set on_surface
      on_surface = next_boundary_.surface->id();
      
      // Set on_side to opposite of the side we were just on
      if(next_boundary_.side == Side::Positive) on_side = Side::Negative;
      else on_side = Side::Positive;
    }
  }

 private:
  Geometry* geometry;
  GeoNode* current_node_;
  Position r_local_;
  Direction u_local_;
  Vector global_to_local;
  uint32_t on_surface;
  Side on_side;
  Boundary next_boundary_;
  bool lost;
};

}  // namespace pmc

#endif