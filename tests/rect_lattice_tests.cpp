#include"papillon/geometry/rect_lattice.hpp"
#include<gtest/gtest.h>

namespace {
  using namespace pmc;

  // Lattice layout
  // z = -0.5
  // --------> y
  // | 1, 2
  // | 3, 4
  // V
  // x
  //
  // z = 0.5
  // --------> y
  // | 5, 6
  // | 7, 8
  // V
  // x
  
  TEST(RectLattice, lattice_tests) {
    // Make lattice for tests
    RectLattice lat({2,2,2}, {1.,1.,1.}, {-1.,-1.,-1.}, 1, "lat1");
    // Set universes for lattice
    lat.set_elements({1,2,3,4,5,6,7,8});
    // Set outside universe
    lat.set_outisde_universe(12);

    EXPECT_EQ(lat.id(), 1);
    EXPECT_EQ(lat.name(), "lat1");
  }
  
  TEST(RectLattice, get_tile) {
    // Make lattice for tests
    RectLattice lat({2,2,2}, {1.,1.,1.}, {-1.,-1.,-1.}, 1, "lat1");
    // Set universes for lattice
    lat.set_elements({1,2,3,4,5,6,7,8});
    // Set outside universe
    lat.set_outisde_universe(12);

    std::array<int32_t,3> ind;
    
    // Make sure can get tile for all lattices
    ind = lat.get_tile({-0.5,-0.5,-0.5},{1,0,0});
    EXPECT_EQ(ind[0],0);
    EXPECT_EQ(ind[1],0);
    EXPECT_EQ(ind[2],0);

    ind = lat.get_tile({-0.5,0.5,-0.5},{1,0,0});
    EXPECT_EQ(ind[0],0);
    EXPECT_EQ(ind[1],1);
    EXPECT_EQ(ind[2],0);

    ind = lat.get_tile({0.5,-0.5,-0.5},{1,0,0});
    EXPECT_EQ(ind[0],1);
    EXPECT_EQ(ind[1],0);
    EXPECT_EQ(ind[2],0);

    ind = lat.get_tile({0.5,0.5,-0.5},{1,0,0});
    EXPECT_EQ(ind[0],1);
    EXPECT_EQ(ind[1],1);
    EXPECT_EQ(ind[2],0);

    ind = lat.get_tile({-0.5,-0.5,0.5},{1,0,0});
    EXPECT_EQ(ind[0],0);
    EXPECT_EQ(ind[1],0);
    EXPECT_EQ(ind[2],1);

    ind = lat.get_tile({-0.5,0.5,0.5},{1,0,0});
    EXPECT_EQ(ind[0],0);
    EXPECT_EQ(ind[1],1);
    EXPECT_EQ(ind[2],1);

    ind = lat.get_tile({0.5,-0.5,0.5},{1,0,0});
    EXPECT_EQ(ind[0],1);
    EXPECT_EQ(ind[1],0);
    EXPECT_EQ(ind[2],1);

    ind = lat.get_tile({0.5,0.5,0.5},{1,0,0});
    EXPECT_EQ(ind[0],1);
    EXPECT_EQ(ind[1],1);
    EXPECT_EQ(ind[2],1);

    
    // Outside indicies
    ind = lat.get_tile({-1.5,-1.5,-1.5},{1,0,0});
    EXPECT_EQ(ind[0],-1);
    EXPECT_EQ(ind[1],-1);
    EXPECT_EQ(ind[2],-1);

    ind = lat.get_tile({-1.5,-0.5,-1.5},{1,0,0});
    EXPECT_EQ(ind[0],-1);
    EXPECT_EQ(ind[1],0);
    EXPECT_EQ(ind[2],-1);
  }

  TEST(RectLattice, get_tile_center) {
    // Make lattice for tests
    RectLattice lat({2,2,2}, {1.,1.,1.}, {-1.,-1.,-1.}, 1, "lat1");
    // Set universes for lattice
    lat.set_elements({1,2,3,4,5,6,7,8});
    // Set outside universe
    lat.set_outisde_universe(12);

    std::array<int32_t,3> ind;
    Position tile(0,0,0);
    
    // Make sure can get tile for all lattices
    ind = lat.get_tile({-0.5,-0.5,-0.5},{1,0,0});
    tile = lat.get_tile_center(ind);
    EXPECT_DOUBLE_EQ(tile.x(), -0.5);
    EXPECT_DOUBLE_EQ(tile.y(), -0.5);
    EXPECT_DOUBLE_EQ(tile.z(), -0.5);

    ind = lat.get_tile({-0.5,0.5,-0.5},{1,0,0});
    tile = lat.get_tile_center(ind);
    EXPECT_DOUBLE_EQ(tile.x(), -0.5);
    EXPECT_DOUBLE_EQ(tile.y(), 0.5);
    EXPECT_DOUBLE_EQ(tile.z(), -0.5);

    ind = lat.get_tile({0.5,-0.5,-0.5},{1,0,0});
    tile = lat.get_tile_center(ind);
    EXPECT_DOUBLE_EQ(tile.x(), 0.5);
    EXPECT_DOUBLE_EQ(tile.y(), -0.5);
    EXPECT_DOUBLE_EQ(tile.z(), -0.5);

    ind = lat.get_tile({0.5,0.5,-0.5},{1,0,0});
    tile = lat.get_tile_center(ind);
    EXPECT_DOUBLE_EQ(tile.x(), 0.5);
    EXPECT_DOUBLE_EQ(tile.y(), 0.5);
    EXPECT_DOUBLE_EQ(tile.z(), -0.5);

    ind = lat.get_tile({-0.5,-0.5,0.5},{1,0,0});
    tile = lat.get_tile_center(ind);
    EXPECT_DOUBLE_EQ(tile.x(), -0.5);
    EXPECT_DOUBLE_EQ(tile.y(), -0.5);
    EXPECT_DOUBLE_EQ(tile.z(), 0.5);

    ind = lat.get_tile({-0.5,0.5,0.5},{1,0,0});
    tile = lat.get_tile_center(ind);
    EXPECT_DOUBLE_EQ(tile.x(), -0.5);
    EXPECT_DOUBLE_EQ(tile.y(), 0.5);
    EXPECT_DOUBLE_EQ(tile.z(), 0.5);

    ind = lat.get_tile({0.5,-0.5,0.5},{1,0,0});
    tile = lat.get_tile_center(ind);
    EXPECT_DOUBLE_EQ(tile.x(), 0.5);
    EXPECT_DOUBLE_EQ(tile.y(), -0.5);
    EXPECT_DOUBLE_EQ(tile.z(), 0.5);

    ind = lat.get_tile({0.5,0.5,0.5},{1,0,0});
    tile = lat.get_tile_center(ind);
    EXPECT_DOUBLE_EQ(tile.x(), 0.5);
    EXPECT_DOUBLE_EQ(tile.y(), 0.5);
    EXPECT_DOUBLE_EQ(tile.z(), 0.5);

    
    // Outside indicies
    ind = lat.get_tile({-1.5,-1.5,-1.5},{1,0,0});
    tile = lat.get_tile_center(ind);
    EXPECT_DOUBLE_EQ(tile.x(), -1.5);
    EXPECT_DOUBLE_EQ(tile.y(), -1.5);
    EXPECT_DOUBLE_EQ(tile.z(), -1.5);

    ind = lat.get_tile({-1.5,-0.5,-1.5},{1,0,0});
    tile = lat.get_tile_center(ind);
    EXPECT_DOUBLE_EQ(tile.x(), -1.5);
    EXPECT_DOUBLE_EQ(tile.y(), -0.5);
    EXPECT_DOUBLE_EQ(tile.z(), -1.5);
  }

  TEST(RectLattice, is_valid_tile) {
    // Make lattice for tests
    RectLattice lat({2,2,2}, {1.,1.,1.}, {-1.,-1.,-1.}, 1, "lat1");
    // Set universes for lattice
    lat.set_elements({1,2,3,4,5,6,7,8});
    // Set outside universe
    lat.set_outisde_universe(12);

    std::array<int32_t,3> ind;
    
    // Make sure can get tile for all lattices
    ind = lat.get_tile({-0.5,-0.5,-0.5},{1,0,0});
    EXPECT_TRUE(lat.is_valid_tile(ind));

    ind = lat.get_tile({-0.5,0.5,-0.5},{1,0,0});
    EXPECT_TRUE(lat.is_valid_tile(ind));

    ind = lat.get_tile({0.5,-0.5,-0.5},{1,0,0});
    EXPECT_TRUE(lat.is_valid_tile(ind));

    ind = lat.get_tile({0.5,0.5,-0.5},{1,0,0});
    EXPECT_TRUE(lat.is_valid_tile(ind));

    ind = lat.get_tile({-0.5,-0.5,0.5},{1,0,0});
    EXPECT_TRUE(lat.is_valid_tile(ind));

    ind = lat.get_tile({-0.5,0.5,0.5},{1,0,0});
    EXPECT_TRUE(lat.is_valid_tile(ind));

    ind = lat.get_tile({0.5,-0.5,0.5},{1,0,0});
    EXPECT_TRUE(lat.is_valid_tile(ind));

    ind = lat.get_tile({0.5,0.5,0.5},{1,0,0});
    EXPECT_TRUE(lat.is_valid_tile(ind));
    
    // Outside indicies
    ind = lat.get_tile({-1.5,-1.5,-1.5},{1,0,0});
    EXPECT_FALSE(lat.is_valid_tile(ind));

    ind = lat.get_tile({-1.5,-0.5,-1.5},{1,0,0});
    EXPECT_FALSE(lat.is_valid_tile(ind));
  }

  TEST(RectLattice, get_tile_universe) {
    // Make lattice for tests
    RectLattice lat({2,2,2}, {1.,1.,1.}, {-1.,-1.,-1.}, 1, "lat1");
    // Set universes for lattice
    lat.set_elements({1,2,3,4,5,6,7,8});
    // Set outside universe
    lat.set_outisde_universe(12);

    std::array<int32_t,3> ind;
    
    // Make sure can get tile for all lattices
    ind = lat.get_tile({-0.5,-0.5,-0.5},{1,0,0});
    EXPECT_EQ(lat.get_tile_universe(ind), 1);

    ind = lat.get_tile({-0.5,0.5,-0.5},{1,0,0});
    EXPECT_EQ(lat.get_tile_universe(ind), 2);

    ind = lat.get_tile({0.5,-0.5,-0.5},{1,0,0});
    EXPECT_EQ(lat.get_tile_universe(ind), 3);

    ind = lat.get_tile({0.5,0.5,-0.5},{1,0,0});
    EXPECT_EQ(lat.get_tile_universe(ind), 4);

    ind = lat.get_tile({-0.5,-0.5,0.5},{1,0,0});
    EXPECT_EQ(lat.get_tile_universe(ind), 5);

    ind = lat.get_tile({-0.5,0.5,0.5},{1,0,0});
    EXPECT_EQ(lat.get_tile_universe(ind), 6);

    ind = lat.get_tile({0.5,-0.5,0.5},{1,0,0});
    EXPECT_EQ(lat.get_tile_universe(ind), 7);

    ind = lat.get_tile({0.5,0.5,0.5},{1,0,0});
    EXPECT_EQ(lat.get_tile_universe(ind), 8);
    
    // Outside indicies
    ind = lat.get_tile({-1.5,-1.5,-1.5},{1,0,0});
    EXPECT_EQ(lat.get_tile_universe(ind), 12);

    ind = lat.get_tile({-1.5,-0.5,-1.5},{1,0,0});
    EXPECT_EQ(lat.get_tile_universe(ind), 12);
  }

  TEST(RectLattice, distance_to_tile_boundary) {
    // Make lattice for tests
    RectLattice lat({2,2,2}, {1.,1.,1.}, {-1.,-1.,-1.}, 1, "lat1");
    // Set universes for lattice
    lat.set_elements({1,2,3,4,5,6,7,8});
    // Set outside universe
    lat.set_outisde_universe(12);

    std::array<int32_t,3> ind, ind_tst;
    std::pair<double,std::array<int32_t,3>> boundary;
    
    // Make sure can get tile for all lattices
    ind = lat.get_tile({-0.5,-0.5,-0.5},{1,0,0});
    boundary = lat.distance_to_tile_boundary({-0.5,-0.5,-0.5},{1.0,0.,0.},ind);
    EXPECT_DOUBLE_EQ(boundary.first, 0.5);
    ind_tst = {1,0,0};
    EXPECT_TRUE(boundary.second == ind_tst);

    
    ind = lat.get_tile({-0.5,-0.5,0.5},{1,0,0});
    boundary = lat.distance_to_tile_boundary({-0.5,-0.5,0.5},{0.0,-1.,0.},ind);
    EXPECT_DOUBLE_EQ(boundary.first, 0.5);
    ind_tst = {0,-1,1};
    EXPECT_TRUE(boundary.second == ind_tst);

    ind = lat.get_tile({0.5,-0.5,0.99},{0,0,1});
    boundary = lat.distance_to_tile_boundary({0.5,-0.5,0.99},{0,0,1},ind);
    EXPECT_DOUBLE_EQ(boundary.first, 1.- 0.99);
    ind_tst = {1,0,2};
    EXPECT_TRUE(boundary.second == ind_tst);
  }

};
