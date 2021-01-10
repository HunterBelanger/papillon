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
#include <Papillon/geometry/csg/intersection.hpp>

namespace pmc {

  Intersection::Intersection(std::shared_ptr<Volume> r1, std::shared_ptr<Volume> r2, uint32_t id): Volume(id), r1_(r1), r2_(r2) {}

  bool Intersection::is_inside(const Position& r, const Direction& u, uint32_t on_surf, Side on_side) const {
    if(!r1_->is_inside(r,u,on_surf,on_side)) return false;
    else return (r2_->is_inside(r,u,on_surf,on_side));
  }

  Ray Intersection::get_ray(const Position& r, const Direction& u) const {
    Ray ray_1 = r1_->get_ray(r, u);

    // Empty ray, no need to check second branch
    if(ray_1.size() == 0) return Ray({});

    Ray ray_2 = r2_->get_ray(r, u);
    if(ray_2.size() == 0) return Ray({});

    // Only try intersection if neither branch is empty
    return ray_1.get_intersection(ray_2);
  }

}