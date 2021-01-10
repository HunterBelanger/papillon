#include"papillon/geometry/hex_lattice.hpp"
#include<gtest/gtest.h>
#include<cmath>

namespace {
  using namespace pmc;
  //=======================================================
  // Pointy Tests
  //-------------------------------------------------------
  // Lattice layout
  // z = -0.5
  // ------------> q 
  //   1,  2    \
  // 3,  4,  5   \
  //   6,  7      r
  //
  //
  // z = 0.5
  // ------------> q 
  //    8,   9    \
  // 10,  11,  12  \
  //    13,  14     r
  //
  
  TEST(HexLattice, pointy_get_tile) {
    // Make lattice
    HexLattice lat({2,2},{1,1},{0,0,0},HexLattice::Top::Pointy,1,"lat2");
    lat.set_elements({1,2,3,4,5,6,7,8,9,10,11,12,13,14});
    lat.set_outisde_universe(15);

    std::array<int32_t,3> ind;
    
    // Center
    ind = lat.get_tile({0,0,-0.5},{0,1,0});
    EXPECT_EQ(ind[0],0);
    EXPECT_EQ(ind[1],0);
    EXPECT_EQ(ind[2],0);
    
    // Z direction
    ind = lat.get_tile({0,0,0.5},{0,1,0});
    EXPECT_EQ(ind[0],0);
    EXPECT_EQ(ind[1],0);
    EXPECT_EQ(ind[2],1);
    
    // Q direction
    ind = lat.get_tile({0,1.,0.5},{0,1,0});
    EXPECT_EQ(ind[0],1);
    EXPECT_EQ(ind[1],0);
    EXPECT_EQ(ind[2],1);

    // -R direction
    ind = lat.get_tile({-std::cos(M_PI/6.),-std::sin(M_PI/6.),0.5},{0,1,0});
    EXPECT_EQ(ind[0],0);
    EXPECT_EQ(ind[1],-1);
    EXPECT_EQ(ind[2],1);

    ind = lat.get_tile({-3.*std::cos(M_PI/6.),-3.*std::sin(M_PI/6.)-1.,2.5},{0,1,0});
    EXPECT_EQ(ind[0],-1);
    EXPECT_EQ(ind[1],-3);
    EXPECT_EQ(ind[2],3);
  }

  TEST(HexLattice, pointy_get_tile_center) {
    //Make lattice
    HexLattice lat({2,2},{1,1},{0,0,0},HexLattice::Top::Pointy,1,"lat2");
    lat.set_elements({1,2,3,4,5,6,7,8,9,10,11,12,13,14});
    lat.set_outisde_universe(15);

    std::array<int32_t,3> ind;
    Position tile(0.,0.,0.);
    Position center(0.,0.,0.);
    
    // Center
    ind = lat.get_tile({0,0,-0.5},{0,1,0});
    center = {0.,0.,-0.5};
    tile = lat.get_tile_center(ind);
    EXPECT_DOUBLE_EQ(tile.x(),center.x());
    EXPECT_DOUBLE_EQ(tile.y(),center.y());
    EXPECT_DOUBLE_EQ(tile.z(),center.z());
    
    // Z direction
    ind = lat.get_tile({0,0,0.5},{0,1,0});
    center = {0.,0.,0.5};
    tile = lat.get_tile_center(ind);
    EXPECT_DOUBLE_EQ(tile.x(),center.x());
    EXPECT_DOUBLE_EQ(tile.y(),center.y());
    EXPECT_DOUBLE_EQ(tile.z(),center.z());
    
    // Q direction
    ind = lat.get_tile({0,1.,0.5},{0,1,0});
    center = {0.,1.,0.5};
    tile = lat.get_tile_center(ind);
    EXPECT_DOUBLE_EQ(tile.x(),center.x());
    EXPECT_DOUBLE_EQ(tile.y(),center.y());
    EXPECT_DOUBLE_EQ(tile.z(),center.z());

    // -R direction
    ind = lat.get_tile({-std::cos(M_PI/6.),-std::sin(M_PI/6.),0.5},{0,1,0});
    center = {-std::cos(M_PI/6.),-std::sin(M_PI/6.),0.5};
    tile = lat.get_tile_center(ind);
    EXPECT_DOUBLE_EQ(tile.x(),center.x());
    EXPECT_DOUBLE_EQ(tile.y(),center.y());
    EXPECT_DOUBLE_EQ(tile.z(),center.z());

    ind = lat.get_tile({-3.*std::cos(M_PI/6.),-3.*std::sin(M_PI/6.)-1.,2.5},{0,1,0});
    center = {-3.*std::cos(M_PI/6.),-3.*std::sin(M_PI/6.)-1.,2.5};
    tile = lat.get_tile_center(ind);
    EXPECT_DOUBLE_EQ(tile.x(),center.x());
    EXPECT_DOUBLE_EQ(tile.y(),center.y());
    EXPECT_DOUBLE_EQ(tile.z(),center.z());
  }

  TEST(HexLattice, pointy_is_valid_tile) {
    //Make lattice
    HexLattice lat({2,2},{1,1},{0,0,0},HexLattice::Top::Pointy,1,"lat2");
    lat.set_elements({1,2,3,4,5,6,7,8,9,10,11,12,13,14});
    lat.set_outisde_universe(15);

    std::array<int32_t,3> ind;
    
    // Center
    ind = lat.get_tile({0,0,-0.5},{0,1,0});
    EXPECT_TRUE(lat.is_valid_tile(ind));

    // Z direction
    ind = lat.get_tile({0,0,0.5},{0,1,0});
    EXPECT_TRUE(lat.is_valid_tile(ind));
        
    // Q direction
    ind = lat.get_tile({0,1.,0.5},{0,1,0});
    EXPECT_TRUE(lat.is_valid_tile(ind));
    
    // -R direction
    ind = lat.get_tile({-std::cos(M_PI/6.),-std::sin(M_PI/6.),0.5},{0,1,0});
    EXPECT_TRUE(lat.is_valid_tile(ind));

    ind = lat.get_tile({-3.*std::cos(M_PI/6.),-3.*std::sin(M_PI/6.)-1.,2.5},{0,1,0});
    EXPECT_FALSE(lat.is_valid_tile(ind));
  }

  TEST(HexLattice, pointy_get_tile_universe) {
    //Make lattice
    HexLattice lat({2,2},{1,1},{0,0,0},HexLattice::Top::Pointy,1,"lat2");
    lat.set_elements({1,2,3,4,5,6,7,8,9,10,11,12,13,14});
    lat.set_outisde_universe(15);

    std::array<int32_t,3> ind;
    
    // Center
    ind = lat.get_tile({0,0,-0.5},{0,1,0});
    EXPECT_TRUE(lat.is_valid_tile(ind));

    // Z direction
    ind = lat.get_tile({0,0,0.5},{0,1,0});
    EXPECT_EQ(lat.get_tile_universe(ind), 11);
        
    // Q direction
    ind = lat.get_tile({0,1.,0.5},{0,1,0});
    EXPECT_EQ(lat.get_tile_universe(ind), 12);
    
    // -R direction
    ind = lat.get_tile({-std::cos(M_PI/6.),-std::sin(M_PI/6.),0.5},{0,1,0});
    EXPECT_EQ(lat.get_tile_universe(ind), 8);

    ind = lat.get_tile({-3.*std::cos(M_PI/6.),-3.*std::sin(M_PI/6.)-1.,2.5},{0,1,0});
    EXPECT_EQ(lat.get_tile_universe(ind), 15);
  }

  TEST(HexLattice, pointy_distance_to_tile_boundary) {
    //Make lattice
    HexLattice lat({2,2},{1,1},{0,0,0},HexLattice::Top::Pointy,1,"lat2");
    lat.set_elements({1,2,3,4,5,6,7,8,9,10,11,12,13,14});
    lat.set_outisde_universe(15);

    std::array<int32_t,3> ind;
    std::pair<double,std::array<int32_t,3>> boundary;
    
    // +Z direction
    ind = lat.get_tile({0,0,-0.5},{0,1,0});
    boundary = lat.distance_to_tile_boundary({0,0,-0.5},{0,0,1},ind);
    EXPECT_DOUBLE_EQ(boundary.first, 0.5);
    EXPECT_EQ(boundary.second[0],0);
    EXPECT_EQ(boundary.second[1],0);
    EXPECT_EQ(boundary.second[2],1);
    
    // -Z direction
    ind = lat.get_tile({0,0,-0.5},{0,1,0});
    boundary = lat.distance_to_tile_boundary({0,0,-0.5},{0,0,-1},ind);
    EXPECT_DOUBLE_EQ(boundary.first, 0.5);
    EXPECT_EQ(boundary.second[0],0);
    EXPECT_EQ(boundary.second[1],0);
    EXPECT_EQ(boundary.second[2],-1);

    // +Q (y) direction
    ind = lat.get_tile({0,0,-0.5},{0,1,0});
    boundary = lat.distance_to_tile_boundary({0,0,-0.5},{0,1,0},ind);
    EXPECT_DOUBLE_EQ(boundary.first, 0.5);
    EXPECT_EQ(boundary.second[0],1);
    EXPECT_EQ(boundary.second[1],0);
    EXPECT_EQ(boundary.second[2],0);
        
    // -Q (y) direction
    ind = lat.get_tile({0,0,-0.5},{0,1,0});
    boundary = lat.distance_to_tile_boundary({0,0,-0.5},{0,-1,0},ind);
    EXPECT_DOUBLE_EQ(boundary.first, 0.5);
    EXPECT_EQ(boundary.second[0],-1);
    EXPECT_EQ(boundary.second[1],0);
    EXPECT_EQ(boundary.second[2],0);
    
    // -R direction
    ind = lat.get_tile({0,0,-0.5},{0,1,0});
    boundary = lat.distance_to_tile_boundary({0,0,-0.5},{-std::cos(M_PI/6.),
                                                         -std::sin(M_PI/6.),0},ind);
    EXPECT_DOUBLE_EQ(boundary.first, 0.5);
    EXPECT_EQ(boundary.second[0],0);
    EXPECT_EQ(boundary.second[1],-1);
    EXPECT_EQ(boundary.second[2],0);
    
    // +R direction
    ind = lat.get_tile({0,0,-0.5},{0,1,0});
    boundary = lat.distance_to_tile_boundary({0,0,-0.5},{std::cos(M_PI/6.),
                                                         std::sin(M_PI/6.),0},ind);
    EXPECT_DOUBLE_EQ(boundary.first, 0.5);
    EXPECT_EQ(boundary.second[0],0);
    EXPECT_EQ(boundary.second[1],1);
    EXPECT_EQ(boundary.second[2],0);

    // -R + Q direction
    ind = lat.get_tile({0,0,-0.5},{0,1,0});
    boundary = lat.distance_to_tile_boundary({0,0,-0.5},{-std::cos(M_PI/6.),
                                                         -std::sin(M_PI/6.)+1,0},ind);
    EXPECT_DOUBLE_EQ(boundary.first, 0.5);
    EXPECT_EQ(boundary.second[0],1);
    EXPECT_EQ(boundary.second[1],-1);
    EXPECT_EQ(boundary.second[2],0);
    
    // +R - Q direction
    ind = lat.get_tile({0,0,-0.5},{0,1,0});
    boundary = lat.distance_to_tile_boundary({0,0,-0.5},{std::cos(M_PI/6.),
                                                         std::sin(M_PI/6.)-1,0},ind);
    EXPECT_DOUBLE_EQ(boundary.first, 0.5);
    EXPECT_EQ(boundary.second[0],-1);
    EXPECT_EQ(boundary.second[1],1);
    EXPECT_EQ(boundary.second[2],0);
  }

  //=======================================================
  // Flat Tests
  //-------------------------------------------------------
  // Lattice layout
  // z = -0.5
  // ------------> q 
  //   1,  2    \
  // 3,  4,  5   \
  //   6,  7      r
  //
  //
  // z = 0.5
  // ------------> q 
  //    8,   9    \
  // 10,  11,  12  \
  //    13,  14     r
  //
  
  TEST(HexLattice, flat_get_tile) {
    // Make lattice
    HexLattice lat({2,2},{1,1},{0,0,0},HexLattice::Top::Flat,1,"lat3");
    lat.set_elements({1,2,3,4,5,6,7,8,9,10,11,12,13,14});
    lat.set_outisde_universe(15);

    std::array<int32_t,3> ind;
    
    // Center
    ind = lat.get_tile({0,0,-0.5},{0,1,0});
    EXPECT_EQ(ind[0],0);
    EXPECT_EQ(ind[1],0);
    EXPECT_EQ(ind[2],0);
    
    // Z direction
    ind = lat.get_tile({0,0,0.5},{0,1,0});
    EXPECT_EQ(ind[0],0);
    EXPECT_EQ(ind[1],0);
    EXPECT_EQ(ind[2],1);
    
    // Q direction
    ind = lat.get_tile({std::cos(M_PI/3.),std::sin(M_PI/3.),0.5},{0,1,0});
    EXPECT_EQ(ind[0],1);
    EXPECT_EQ(ind[1],0);
    EXPECT_EQ(ind[2],1);

    // -R direction
    ind = lat.get_tile({-1,0.,0.5},{0,1,0});
    EXPECT_EQ(ind[0],0);
    EXPECT_EQ(ind[1],-1);
    EXPECT_EQ(ind[2],1);
    
    // -3Q + R + 2Z direction
    ind = lat.get_tile({-3.*std::cos(M_PI/3.)-1,-3.*std::sin(M_PI/3.),2.5},{0,1,0});
    EXPECT_EQ(ind[0],-3);
    EXPECT_EQ(ind[1],-1);
    EXPECT_EQ(ind[2],3);
  }

  TEST(HexLattice, flat_get_tile_center) {
    // Make lattice
    HexLattice lat({2,2},{1,1},{0,0,0},HexLattice::Top::Flat,1,"lat3");
    lat.set_elements({1,2,3,4,5,6,7,8,9,10,11,12,13,14});
    lat.set_outisde_universe(15);

    std::array<int32_t,3> ind;
    Position tile(0.,0.,0.);
    Position center(0.,0.,0.);

    // Center
    ind = lat.get_tile({0,0,-0.5},{0,1,0});
    center = {0,0,-0.5};
    tile = lat.get_tile_center(ind);
    EXPECT_DOUBLE_EQ(tile.x(),center.x());
    EXPECT_DOUBLE_EQ(tile.y(),center.y());
    EXPECT_DOUBLE_EQ(tile.z(),center.z());

    // Z direction
    ind = lat.get_tile({0,0,0.5},{0,1,0});
    center = {0.,0.,0.5};
    tile = lat.get_tile_center(ind);
    EXPECT_DOUBLE_EQ(tile.x(),center.x());
    EXPECT_DOUBLE_EQ(tile.y(),center.y());
    EXPECT_DOUBLE_EQ(tile.z(),center.z());

    // Q direction
    ind = lat.get_tile({std::cos(M_PI/3.),std::sin(M_PI/3.),0.5},{0,1,0});
    center = {std::cos(M_PI/3.),std::sin(M_PI/3.),0.5};
    tile = lat.get_tile_center(ind);
    EXPECT_DOUBLE_EQ(tile.x(),center.x());
    EXPECT_DOUBLE_EQ(tile.y(),center.y());
    EXPECT_DOUBLE_EQ(tile.z(),center.z());

    // -R direction
    ind = lat.get_tile({-1,0.,0.5},{0,1,0});
    center = {-1.,0.,0.5};
    tile = lat.get_tile_center(ind);
    EXPECT_DOUBLE_EQ(tile.x(),center.x());
    EXPECT_DOUBLE_EQ(tile.y(),center.y());
    EXPECT_DOUBLE_EQ(tile.z(),center.z());
    
    // -3Q + R + 2Z direction
    ind = lat.get_tile({-3.*std::cos(M_PI/3.)-1,-3.*std::sin(M_PI/3.),2.5},{0,1,0});
    center = {-3.*std::cos(M_PI/3.)-1,-3.*std::sin(M_PI/3.),2.5};
    tile = lat.get_tile_center(ind);
    EXPECT_DOUBLE_EQ(tile.x(),center.x());
    EXPECT_DOUBLE_EQ(tile.y(),center.y());
    EXPECT_DOUBLE_EQ(tile.z(),center.z());
  }

  TEST(HexLattice, flat_is_valid_tile) {
    // Make lattice
    HexLattice lat({2,2},{1,1},{0,0,0},HexLattice::Top::Flat,1,"lat3");
    lat.set_elements({1,2,3,4,5,6,7,8,9,10,11,12,13,14});
    lat.set_outisde_universe(15);

    std::array<int32_t,3> ind;

    // Center
    ind = lat.get_tile({0,0,-0.5},{0,1,0});
    EXPECT_TRUE(lat.is_valid_tile(ind));

    // Z direction
    ind = lat.get_tile({0,0,0.5},{0,1,0});
    EXPECT_TRUE(lat.is_valid_tile(ind));

    // Q direction
    ind = lat.get_tile({std::cos(M_PI/3.),std::sin(M_PI/3.),0.5},{0,1,0});
    EXPECT_TRUE(lat.is_valid_tile(ind));

    // -R direction
    ind = lat.get_tile({-1,0.,0.5},{0,1,0});
    EXPECT_TRUE(lat.is_valid_tile(ind));
    
    // -3Q + R + 2Z direction
    ind = lat.get_tile({-3.*std::cos(M_PI/3.)-1,-3.*std::sin(M_PI/3.),2.5},{0,1,0});
    EXPECT_FALSE(lat.is_valid_tile(ind));
  }

  TEST(HexLattice, flat_get_tile_universe) {
    // Make lattice
    HexLattice lat({2,2},{1,1},{0,0,0},HexLattice::Top::Flat,1,"lat3");
    lat.set_elements({1,2,3,4,5,6,7,8,9,10,11,12,13,14});
    lat.set_outisde_universe(15);

    std::array<int32_t,3> ind;

    // Center
    ind = lat.get_tile({0,0,-0.5},{0,1,0});
    EXPECT_EQ(lat.get_tile_universe(ind), 4);

    // Z direction
    ind = lat.get_tile({0,0,0.5},{0,1,0});
    EXPECT_EQ(lat.get_tile_universe(ind), 11);

    // Q direction
    ind = lat.get_tile({std::cos(M_PI/3.),std::sin(M_PI/3.),0.5},{0,1,0});
    EXPECT_EQ(lat.get_tile_universe(ind), 12);

    // R direction
    ind = lat.get_tile({1,0.,0.5},{0,1,0});
    EXPECT_EQ(lat.get_tile_universe(ind), 14);
    
    // -3Q + R + 2Z direction
    ind = lat.get_tile({-3.*std::cos(M_PI/3.)-1,-3.*std::sin(M_PI/3.),2.5},{0,1,0});
    EXPECT_EQ(lat.get_tile_universe(ind), 15);
  }

  TEST(HexLattice, flat_distance_to_tile_boundary) {
    // Make lattice
    HexLattice lat({2,2},{1,1},{0,0,0},HexLattice::Top::Flat,1,"lat3");
    lat.set_elements({1,2,3,4,5,6,7,8,9,10,11,12,13,14});
    lat.set_outisde_universe(15);

    std::array<int32_t,3> ind;
    std::pair<double,std::array<int32_t,3>> boundary;

    // +Z Direction
    ind = lat.get_tile({0,0,-0.5},{0,1,0});
    boundary = lat.distance_to_tile_boundary({0,0,-0.5},{0,0,1},ind);
    EXPECT_DOUBLE_EQ(boundary.first, 0.5);
    EXPECT_EQ(boundary.second[0],0);
    EXPECT_EQ(boundary.second[1],0);
    EXPECT_EQ(boundary.second[2],1);

    // -Z Direction
    ind = lat.get_tile({0,0,-0.5},{0,1,0});
    boundary = lat.distance_to_tile_boundary({0,0,-0.5},{0,0,-1},ind);
    EXPECT_DOUBLE_EQ(boundary.first, 0.5);
    EXPECT_EQ(boundary.second[0],0);
    EXPECT_EQ(boundary.second[1],0);
    EXPECT_EQ(boundary.second[2],-1);

    // +R Direction
    ind = lat.get_tile({0,0,-0.5},{0,1,0});
    boundary = lat.distance_to_tile_boundary({0,0,-0.5},{1,0,0},ind);
    EXPECT_DOUBLE_EQ(boundary.first, 0.5);
    EXPECT_EQ(boundary.second[0],0);
    EXPECT_EQ(boundary.second[1],1);
    EXPECT_EQ(boundary.second[2],0);

    // -R Direction
    ind = lat.get_tile({0,0,-0.5},{0,1,0});
    boundary = lat.distance_to_tile_boundary({0,0,-0.5},{-1,0,0},ind);
    EXPECT_DOUBLE_EQ(boundary.first, 0.5);
    EXPECT_EQ(boundary.second[0],0);
    EXPECT_EQ(boundary.second[1],-1);
    EXPECT_EQ(boundary.second[2],0);

    // +Q Direction
    ind = lat.get_tile({0,0,-0.5},{0,1,0});
    boundary = lat.distance_to_tile_boundary({0,0,-0.5},{std::cos(M_PI/3.),
                                                         std::sin(M_PI/3.),0},ind);
    EXPECT_DOUBLE_EQ(boundary.first, 0.5);
    EXPECT_EQ(boundary.second[0],1);
    EXPECT_EQ(boundary.second[1],0);
    EXPECT_EQ(boundary.second[2],0);

    // -Q Direction
    ind = lat.get_tile({0,0,-0.5},{0,1,0});
    boundary = lat.distance_to_tile_boundary({0,0,-0.5},{-std::cos(M_PI/3.),
                                                         -std::sin(M_PI/3.),0},ind);
    EXPECT_DOUBLE_EQ(boundary.first, 0.5);
    EXPECT_EQ(boundary.second[0],-1);
    EXPECT_EQ(boundary.second[1],0);
    EXPECT_EQ(boundary.second[2],0);

    // +Q - R Direction
    ind = lat.get_tile({0,0,-0.5},{0,1,0});
    boundary = lat.distance_to_tile_boundary({0,0,-0.5},{std::cos(M_PI/3.)-1.,
                                                         std::sin(M_PI/3.),0},ind);
    EXPECT_DOUBLE_EQ(boundary.first, 0.5);
    EXPECT_EQ(boundary.second[0],1);
    EXPECT_EQ(boundary.second[1],-1);
    EXPECT_EQ(boundary.second[2],0);

    // -Q + R Direction
    ind = lat.get_tile({0,0,-0.5},{0,1,0});
    boundary = lat.distance_to_tile_boundary({0,0,-0.5},{-std::cos(M_PI/3.)+1.,
                                                         -std::sin(M_PI/3.),0},ind);
    EXPECT_DOUBLE_EQ(boundary.first, 0.5);
    EXPECT_EQ(boundary.second[0],-1);
    EXPECT_EQ(boundary.second[1],1);
    EXPECT_EQ(boundary.second[2],0);
  }
};
