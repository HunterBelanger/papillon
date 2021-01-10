#include"papillon/geometry/cell.hpp"
#include"papillon/geometry/rect_lattice.hpp"
#include"papillon/geometry/csg/half_space.hpp"
#include"papillon/geometry/surfaces/all_surfaces.hpp"
#include"papillon/geometry/rect_lattice.hpp"
#include"papillon/geometry/geometry.hpp"

#include<memory>
#include<gtest/gtest.h>

namespace {
  using namespace pmc;

  TEST(Cell, is_inside_region) {
    std::shared_ptr<Surface> xp = std::make_shared<XPlane>(3.,Surface::BoundaryType::Normal,1,"xplane");
    std::shared_ptr<Region> reg = std::make_shared<HalfSpace>(xp,true);
    Cell cell(reg,Cell::Fill::Material,0,12,"First cell");

    EXPECT_TRUE(cell.is_inside({4.,0.,0.},{1.,0.,0.},0));
    EXPECT_FALSE(cell.is_inside({2.99,0.,0.},{1.,0.,0.},0));
  }

  TEST(Cell, region_region) {
    std::shared_ptr<Surface> xp = std::make_shared<XPlane>(3.,Surface::BoundaryType::Normal,1,"xplane");
    std::shared_ptr<Region> reg = std::make_shared<HalfSpace>(xp,true);
    Cell cell(reg,Cell::Fill::Material,0,12,"First cell");

    EXPECT_EQ(reg, cell.region());
  }

  TEST(Cell, is_inside_lattice) {
    // Make lattice for tests
    std::shared_ptr<Lattice> lat(new RectLattice({2,2,2}, {1.,1.,1.}, {-1.,-1.,-1.}, 1, "lat1"));
    // Set universes for lattice
    lat->set_elements({1,2,3,4,5,6,7,8});
    // Set outside universe
    lat->set_outisde_universe(12);
    // Add lat to lattice map
    geometry::lattices[lat->id()] = lat;

    // Make cell
    Cell cell(lat->id(), 12, "cell_lat");


    // Perform is_inside test
    EXPECT_TRUE(cell.is_inside({-0.99, -0.99, -0.99},{1.,1.,1.},0));
    EXPECT_TRUE(cell.is_inside({0., 0., 0.},{1.,1.,1.},0));
    EXPECT_TRUE(cell.is_inside({0.99, 0.99, 0.99},{-1.,-1.,-1.},0));

    EXPECT_FALSE(cell.is_inside({1.01, 0.99, 0.99},{-1.,-1.,-1.},0));

    // Clear lattice array before continuing !
    geometry::lattices.clear();
  }

  TEST(Cell, region_lattice) {
    // Make lattice for tests
    std::shared_ptr<Lattice> lat(new RectLattice({2,2,2}, {1.,1.,1.}, {-1.,-1.,-1.}, 1, "lat1"));
    // Set universes for lattice
    lat->set_elements({1,2,3,4,5,6,7,8});
    // Set outside universe
    lat->set_outisde_universe(12);
    // Add lat to lattice map
    geometry::lattices[lat->id()] = lat;

    // Make cell
    Cell cell(lat->id(), 12, "cell_lat");


    // Perform region test
    EXPECT_FALSE(cell.region());

    // Clear lattice array before reseting pointer !
    geometry::lattices.clear();
  }

  TEST(Cell, fill_type) {
    std::shared_ptr<Surface> xp = std::make_shared<XPlane>(3.,Surface::BoundaryType::Normal,1,"xplane");
    std::shared_ptr<Region> reg = std::make_shared<HalfSpace>(xp,true);
    Cell cell(reg,Cell::Fill::Material,0,12,"First cell");

    EXPECT_EQ(cell.fill_type(), Cell::Fill::Material);
  }

  TEST(Cell, fill_id) {
    std::shared_ptr<Surface> xp = std::make_shared<XPlane>(3.,Surface::BoundaryType::Normal,1,"xplane");
    std::shared_ptr<Region> reg = std::make_shared<HalfSpace>(xp,true);
    Cell cell(reg,Cell::Fill::Material,0,12,"First cell");

    EXPECT_EQ(cell.fill_id(), 0);
  }

  TEST(Cell, id) {
    std::shared_ptr<Surface> xp = std::make_shared<XPlane>(3.,Surface::BoundaryType::Normal,1,"xplane");
    std::shared_ptr<Region> reg = std::make_shared<HalfSpace>(xp,true);
    Cell cell(reg,Cell::Fill::Material,0,12,"First cell");

    EXPECT_EQ(cell.id(), 12);
  }

  TEST(Cell, name) {
    std::shared_ptr<Surface> xp = std::make_shared<XPlane>(3.,Surface::BoundaryType::Normal,1,"xplane");
    std::shared_ptr<Region> reg = std::make_shared<HalfSpace>(xp,true);
    Cell cell(reg,Cell::Fill::Material,0,12,"First cell");

    EXPECT_EQ(cell.id(), 12);
  }

};
