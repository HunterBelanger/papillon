#include"papillon/geometry/geo_navigator.hpp"
#include"papillon/geometry/surfaces/all_surfaces.hpp"
#include"papillon/geometry/csg/region.hpp"
#include"papillon/geometry/csg/half_space.hpp"
#include"papillon/geometry/csg/intersection.hpp"
#include"papillon/geometry/csg/difference.hpp"
#include"papillon/geometry/cell.hpp"
#include"papillon/geometry/universe.hpp"
#include"papillon/geometry/rect_lattice.hpp"

#include<gtest/gtest.h>

namespace {
  using namespace pmc;

  void define_nested_box_test_geometry() {
    // Define surfaces for a box at the origin
    geometry::surfaces[1] = std::make_shared<XPlane>(-1.,Surface::BoundaryType::Normal,1,"x0");
    geometry::surfaces[2] = std::make_shared<XPlane>(1.,Surface::BoundaryType::Normal,2,"x1");
    geometry::surfaces[3] = std::make_shared<YPlane>(-1.,Surface::BoundaryType::Normal,3,"y0");
    geometry::surfaces[4] = std::make_shared<YPlane>(1.,Surface::BoundaryType::Normal,4,"y1");
    geometry::surfaces[5] = std::make_shared<ZPlane>(-1.,Surface::BoundaryType::Normal,5,"z0");
    geometry::surfaces[6] = std::make_shared<ZPlane>(1.,Surface::BoundaryType::Normal,6,"z1");

    // Define all half spaces for box
    std::shared_ptr<Region> px = std::make_shared<HalfSpace>(geometry::surfaces[1],true);
    std::shared_ptr<Region> nx = std::make_shared<HalfSpace>(geometry::surfaces[2],false);
    std::shared_ptr<Region> py = std::make_shared<HalfSpace>(geometry::surfaces[3],true);
    std::shared_ptr<Region> ny = std::make_shared<HalfSpace>(geometry::surfaces[4],false);
    std::shared_ptr<Region> pz = std::make_shared<HalfSpace>(geometry::surfaces[5],true);
    std::shared_ptr<Region> nz = std::make_shared<HalfSpace>(geometry::surfaces[6],false);

    std::shared_ptr<Region> xinter = std::make_shared<Intersection>(px,nx);
    std::shared_ptr<Region> yinter = std::make_shared<Intersection>(py,ny);
    std::shared_ptr<Region> zinter = std::make_shared<Intersection>(pz,nz);

    std::shared_ptr<Region> xyinter = std::make_shared<Intersection>(xinter,yinter);
    std::shared_ptr<Region> box_reg = std::make_shared<Intersection>(xyinter, zinter);

    // Make cell
    geometry::cells[1] = std::make_shared<Cell>(box_reg,Cell::Fill::Material,12,1,"box");

    // Make one universe
    std::vector<uint32_t> cells {1};
    geometry::universes[1] = std::make_shared<Universe>(cells,1,"inner");

    // Now make larger box in another universe
    geometry::surfaces[7] = std::make_shared<XPlane>(-2.,Surface::BoundaryType::Normal,7,"x0");
    geometry::surfaces[8] = std::make_shared<XPlane>(2.,Surface::BoundaryType::Normal,8,"x1");
    geometry::surfaces[9] = std::make_shared<YPlane>(-2.,Surface::BoundaryType::Normal,9,"y0");
    geometry::surfaces[10] = std::make_shared<YPlane>(2.,Surface::BoundaryType::Normal,10,"y1");
    geometry::surfaces[11] = std::make_shared<ZPlane>(-2.,Surface::BoundaryType::Normal,11,"z0");
    geometry::surfaces[12] = std::make_shared<ZPlane>(2.,Surface::BoundaryType::Normal,12,"z1");

    // Define all half spaces for box
    std::shared_ptr<Region> px1 = std::make_shared<HalfSpace>(geometry::surfaces[7],true);
    std::shared_ptr<Region> nx1 = std::make_shared<HalfSpace>(geometry::surfaces[8],false);
    std::shared_ptr<Region> py1 = std::make_shared<HalfSpace>(geometry::surfaces[9],true);
    std::shared_ptr<Region> ny1 = std::make_shared<HalfSpace>(geometry::surfaces[10],false);
    std::shared_ptr<Region> pz1 = std::make_shared<HalfSpace>(geometry::surfaces[11],true);
    std::shared_ptr<Region> nz1 = std::make_shared<HalfSpace>(geometry::surfaces[12],false);

    std::shared_ptr<Region> xinter1 = std::make_shared<Intersection>(px1,nx1);
    std::shared_ptr<Region> yinter1 = std::make_shared<Intersection>(py1,ny1);
    std::shared_ptr<Region> zinter1 = std::make_shared<Intersection>(pz1,nz1);

    std::shared_ptr<Region> xyinter1 = std::make_shared<Intersection>(xinter1,yinter1);
    std::shared_ptr<Region> box_reg1 = std::make_shared<Intersection>(xyinter1, zinter1);

    // Make cell
    geometry::cells[2] = std::make_shared<Cell>(box_reg,Cell::Fill::Universe,1,2,"box2");

    // Make one universe
    std::vector<uint32_t> cells1 {2};
    geometry::universes[2] = std::make_shared<Universe>(cells1,2,"root");
    geometry::root_universe_id = 2;
  }

  void define_lattice_test_geometry() {
    // Define surfaces for a pin cell
    geometry::surfaces[1] = std::make_shared<XPlane>(-1.,Surface::BoundaryType::Normal,1,"x0");
    geometry::surfaces[2] = std::make_shared<XPlane>(1.,Surface::BoundaryType::Normal,2,"x1");
    geometry::surfaces[3] = std::make_shared<YPlane>(-1.,Surface::BoundaryType::Normal,3,"y0");
    geometry::surfaces[4] = std::make_shared<YPlane>(1.,Surface::BoundaryType::Normal,4,"y1");
    geometry::surfaces[5] = std::make_shared<ZPlane>(-5.,Surface::BoundaryType::Normal,5,"z0");
    geometry::surfaces[6] = std::make_shared<ZPlane>(5.,Surface::BoundaryType::Normal,6,"z1");
    geometry::surfaces[7] = std::make_shared<ZCylinder>(0.,0.,0.7,Surface::BoundaryType::Normal,7,"zcyl");

    // Define all half spaces for outer bounds of cell
    std::shared_ptr<Region> px = std::make_shared<HalfSpace>(geometry::surfaces[1],true);
    std::shared_ptr<Region> nx = std::make_shared<HalfSpace>(geometry::surfaces[2],false);
    std::shared_ptr<Region> py = std::make_shared<HalfSpace>(geometry::surfaces[3],true);
    std::shared_ptr<Region> ny = std::make_shared<HalfSpace>(geometry::surfaces[4],false);
    std::shared_ptr<Region> pz = std::make_shared<HalfSpace>(geometry::surfaces[5],true);
    std::shared_ptr<Region> nz = std::make_shared<HalfSpace>(geometry::surfaces[6],false);

    // Half space for inside cylinder
    std::shared_ptr<Region> ncyl = std::make_shared<HalfSpace>(geometry::surfaces[7],false);

    // Make pin region
    std::shared_ptr<Region> pin_z_top = std::make_shared<Intersection>(ncyl,nz);
    std::shared_ptr<Region> pin_region = std::make_shared<Intersection>(pin_z_top,pz);

    // Make moderator region
    std::shared_ptr<Region> xinter = std::make_shared<Intersection>(px,nx);
    std::shared_ptr<Region> yinter = std::make_shared<Intersection>(py,ny);
    std::shared_ptr<Region> zinter = std::make_shared<Intersection>(pz,nz);
    std::shared_ptr<Region> xyinter = std::make_shared<Intersection>(xinter,yinter);
    std::shared_ptr<Region> box_reg = std::make_shared<Intersection>(xyinter, zinter);
    std::shared_ptr<Region> mod_region = std::make_shared<Difference>(box_reg,pin_region);

    // Make cell for pin and moderator
    geometry::cells[1] = std::make_shared<Cell>(pin_region,Cell::Fill::Material,12,1,"pin");
    geometry::cells[2] = std::make_shared<Cell>(mod_region,Cell::Fill::Material,13,2,"mod");

    // Make another cell for pin and moderator
    geometry::cells[3] = std::make_shared<Cell>(pin_region,Cell::Fill::Material,14,3,"pin2");
    geometry::cells[4] = std::make_shared<Cell>(mod_region,Cell::Fill::Material,15,4,"mod2");

    // Make lattice tile universe
    std::vector<uint32_t> cells {1,2};
    geometry::universes[1] = std::make_shared<Universe>(cells,1,"pin cell");

    // Make another lattice tile universe
    std::vector<uint32_t> cells2 {3,4};
    geometry::universes[2] = std::make_shared<Universe>(cells2,2,"pin cell 2");

    // Make lattice (4x4)
    geometry::lattices[1] = std::make_shared<RectLattice>(2,2,1,2.,2.,10.,-2.,-2.,-5.,1,"latt");
    geometry::lattices[1]->set_elements({1,1,1,2});

    // Make cell with lattice
    geometry::cells[5] = std::make_shared<Cell>(1,5,"latt cell");

    // Make root universe
    std::vector<uint32_t> cells_root {5};
    geometry::universes[3] = std::make_shared<Universe>(cells_root,3,"root");
    geometry::root_universe_id = 3;
  }

  void cleanup_geometry() {
    geometry::cells.clear();
    geometry::universes.clear();
    geometry::surfaces.clear();
    geometry::lattices.clear();
  }

  TEST(GeoNavigator, current_cell_boxes) {
    define_nested_box_test_geometry(); 
    
    // Put a position inside the box
    Position r{0.5,0.5,0.5};
    Direction u{1.,0.,0.};

    GeoNavigator nav(r,u);

    std::shared_ptr<Cell> cell = nav.current_cell();
    
    EXPECT_EQ(cell->id(), 1);
    EXPECT_EQ(cell->name(), "box");

    GeoNavigator nav2({0.5,0.5,1.1},{1.,0.,0.});

    std::shared_ptr<Cell> cell2 = nav2.current_cell();
    EXPECT_FALSE(cell2);
    

    cleanup_geometry();
  }

  TEST(GeoNavigator, current_cell_lattice) {
    define_lattice_test_geometry();
    
    // Get a position and direction
    Position r{-1.,-1.,0.};
    Direction u{1.,0.,0.};
    GeoNavigator nav(r,u);
    std::shared_ptr<Cell> cell = nav.current_cell();
    EXPECT_TRUE(cell);
    EXPECT_EQ(cell->id(), 1);
    EXPECT_EQ(cell->name(), "pin");

    Position r2{-1.+0.71,-1.,0.};
    GeoNavigator nav2(r2,u);
    cell = nav2.current_cell();
    EXPECT_TRUE(cell);
    EXPECT_EQ(cell->id(), 2);
    EXPECT_EQ(cell->name(), "mod");

    Position r3{1.+0.71,1.,0.};
    GeoNavigator nav3(r3,u);
    cell = nav3.current_cell();
    EXPECT_TRUE(cell);
    EXPECT_EQ(cell->id(), 4);
    EXPECT_EQ(cell->name(), "mod2");

    cleanup_geometry(); 
  }

};
