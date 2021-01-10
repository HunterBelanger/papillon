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
#ifndef PAPILLON_SURFACE_H
#define PAPILLON_SURFACE_H

#include <Papillon/geometry/ray.hpp>
#include <Papillon/utils/direction.hpp>
#include <memory>

namespace pmc {

class Surface {
 public:
  enum class BoundaryType { Transparent, Vacuum, Reflective };
  
  Surface(BoundaryType boundary, uint32_t id) : id_(id), boundary_(boundary) {
    if (id_ == 0) {
      std::string mssg = "surface id must be > 0.";
      throw PMCException(mssg, __FILE__, __LINE__);
    }
  }
  virtual ~Surface() = default;

  virtual Side sign(const Position& r, const Direction& u) const = 0;
  virtual double distance(const Position& r, const Direction& u) const = 0;
  virtual Direction normal(const Position& r) const = 0;
  virtual Ray get_ray(const Position& r, const Direction& u, Side side) const = 0;
  virtual void translate(const Vector& v) = 0;

  virtual std::shared_ptr<Surface> clone() const = 0;

  BoundaryType boundary() const { return boundary_; }
  uint32_t id() const { return id_; }

 protected:
  uint32_t id_;
  BoundaryType boundary_;
};

}  // namespace pmc

#endif