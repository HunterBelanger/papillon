#include <Papillon/geometry/surfaces/sphere.hpp>
#include <Papillon/geometry/csg/half_space.hpp>
#include <Papillon/geometry/geo_navigator.hpp>
#include <Papillon/utils/transformation.hpp>

//#include <Papillon/plotter/geo_plotter.hpp>

#include <iostream>
#include <memory>

const std::string papillon_logo = "\n"
  "                         .==-.                   .-==.\n"
  "                          \\() `-._  `.   .'  _.-' ()/\n"
  "                          (88\"   ::.  \\./  .::   \"88)\n"
  "                           \\_.'`-::::.(#).::::-'`._/\n"
  "                             `._... . (_) . ..._.'\n"
  "                               \"\"-..-'|=|`-..-\"\"\n"
  "                               .\"\"' .'|=|`. `\"\".\n"
  "                             ,':8(o)./|=|\\.(o)8:`.\n"
  "                            (O :8 ::/ \\_/ \\:: 8: O)\n"
  "                             \\O `::/       \\::' O/\n"
  "                              \"\"--'         `--\"\"\n" 
  "                      _____            _ _ _\n"             
  "                     |  __ \\          (_) | |\n"            
  "                     | |__) |_ _ _ __  _| | | ___  _ __\n"  
  "                     |  ___/ _` | '_ \\| | | |/ _ \\| '_ \\ \n"
  "                     | |  | (_| | |_) | | | | (_) | | | |\n"
  "                     |_|   \\__,_| .__/|_|_|_|\\___/|_| |_|\n"
  "                                | |\n"                      
  "                                |_|\n\n";

const std::string papillon_header = 
  "                          Monte Carlo Transport Code\n"
  "                     Copyright (c) 2020,  Hunter Belanger\n"
  "                    Released under the CeCILL v2.1 licnese\n\n";

const std::string papillon_help =
  " Papillon is a continuous energy, neutral particle, Monte Carlo\n"
  " transport code. It may be used to to solve fixed source, or\n"
  " k eigenvalue problems for neutrons. For more information,\n"
  " visit https://github.com/HunterBelanger/papillon\n\n"

  " Usage:\n"
#ifdef _OPENMP
  "   papillon (--input FILE) [--threads NUM --output FILE]\n"
#else
  "   papillon (--input FILE) [--output FILE]\n"
#endif
  "   papillon (--input FILE --plot) [--threads NUM]\n"
  "   papillon (-l | --license)\n"
  "   papillon (-h | --help)\n"
  "   papillon (-v | --version)\n\n"

  " Options:\n"
  "   -h --help         Show this screen\n"
  "   -v --version      Show version number\n"
  "   -l --license      Show license for Papillon\n"
  "   -i --input FILE   Set input file\n"
#ifdef _OPENMP
  "   -t --threads NUM  Set number of OpenMP threads\n"
#endif
  "   -o --output FILE  Set output file\n"
  "   -p --plot         Start Papillon in plotting mode\n";




using namespace pmc;

int main() {

  std::cout << papillon_logo;
  std::cout << papillon_header;

  std::unordered_map<uint32_t, std::shared_ptr<Surface>> surfaces;
  std::unordered_map<uint32_t, std::shared_ptr<Volume>> volumes;

  surfaces[1] = std::make_shared<Sphere>(0.,0.,0.,2.,Surface::BoundaryType::Transparent,1);
  surfaces[2] = std::make_shared<Sphere>(0.,0.,0.,5.,Surface::BoundaryType::Vacuum,2);

  volumes[1] = std::make_shared<HalfSpace>(surfaces[1], Side::Negative, 1);
  volumes[2] = std::make_shared<HalfSpace>(surfaces[2], Side::Negative, 1);

  std::unique_ptr<GeoNode> root = std::make_unique<GeoNode>(volumes[2],Vector(), "outer_sphere");
  root->add_node(volumes[1], Vector(0.,0.,0.), "inner_sphere");

  Geometry geometry(surfaces, volumes, std::move(root));

  GeoNavigator nav1(&geometry, Position(0.,0.,0.), Direction(1.,0.,0.));

  GeoNode* current1 = nav1.current_node();
  std::cout << current1->name() << std::endl;
  Boundary b1 = nav1.find_next_boundary();
  std::cout << " Next boundary in " << b1.distance << "cm with surface ";
  std::cout << b1.surface->id() << "\n\n";

  // Move by 2.1
  nav1.move_distance(2.1);
  nav1.find_location_from_current();
  
  current1 = nav1.current_node();
  std::cout << current1->name() << std::endl;
  b1 = nav1.find_next_boundary();
  std::cout << " Next boundary in " << b1.distance << "cm with surface ";
  std::cout << b1.surface->id() << "\n";

  nav1.move_distance(b1.distance);
  nav1.set_on_surface(2, Side::Negative);
  nav1.find_location_from_current();
  if(nav1.is_lost()) {
    b1 = nav1.find_next_boundary();
    std::cout << " Nav1 is lost. Distance to surface = " << b1.distance << "\n";
  }

  Vector v(1.,0.,0.);
  Direction u = v;
  std::cout << v << std::endl;

  //GeoPlotter plotter(&geometry);
  //return plotter.run();
}
