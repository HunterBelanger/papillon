#include"papillon/geometry/universe.hpp"
#include<gtest/gtest.h>

namespace {
  using namespace pmc;

  TEST(Universe, size) {
    Universe u({3,4,5},2,"uni"); 

    EXPECT_EQ(u.size(), 3);
  }

  TEST(Universe, index) {
    Universe u({3,4,5},2,"uni"); 

    EXPECT_EQ(u[0], 3);
    EXPECT_EQ(u[1], 4);
    EXPECT_EQ(u[2], 5);
  }

  TEST(Universe, id) {
    Universe u({3,4,5},2,"uni");

    EXPECT_EQ(u.id(), 2); 
  }

  TEST(Universe, name) {
    Universe u({3,4,5},2,"uni");

    EXPECT_EQ(u.name(), "uni");
  }

};
