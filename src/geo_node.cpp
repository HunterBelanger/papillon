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

#include <Papillon/geometry/geo_node.hpp>

namespace pmc {

GeoNode::GeoNode(std::shared_ptr<Volume> v, const std::string& name)
    : name_(name), parent_(nullptr), volume_(v), translation_(), children_() {}
GeoNode::GeoNode(std::shared_ptr<Volume> v, Vector t, const std::string& name)
    : name_(name),
      parent_(nullptr),
      volume_(v),
      translation_(-1 * t),
      children_() {}
GeoNode::GeoNode(GeoNode* p, std::shared_ptr<Volume> v, Vector t,
                 const std::string& name)
    : name_(name), parent_(p), volume_(v), translation_(-1 * t), children_() {}

//============================================================================
// Methods to add nodes
GeoNode* GeoNode::add_node(std::shared_ptr<Volume> v, Vector t,
                           std::string name) {
  children_.emplace_back(std::make_unique<GeoNode>(this, v, t, name));
  return children_.back().get();
}

GeoNode* GeoNode::add_node(std::unique_ptr<GeoNode> node, Vector t) {
  children_.push_back(std::move(node));
  children_.back()->set_parent(this);
  children_.back()->set_translation(t);
  return children_.back().get();
}

GeoNode* GeoNode::add_node(std::unique_ptr<GeoNode> node) {
  children_.push_back(std::move(node));
  children_.back()->set_parent(this);
  return children_.back().get();
}

//============================================================================
// Cloning
std::unique_ptr<GeoNode> GeoNode::clone() const {
  std::unique_ptr<GeoNode> new_this =
      std::make_unique<GeoNode>(volume_, translation_, name_);

  // Add clones of all children
  for (const auto& child : children_) {
    new_this->add_node(std::move(child->clone()));
  }

  return new_this;
}

//============================================================================
// Setters
void GeoNode::set_parent(GeoNode* p) { parent_ = p; }

void GeoNode::set_translation(Vector t) { translation_ = t; }

void GeoNode::set_name(const std::string& name) { name_ = name; }

}  // namespace pmc