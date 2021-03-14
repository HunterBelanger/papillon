#include <Papillon/geometry/surfaces/yplane.hpp>
#include <Papillon/utils/constants.hpp>
#include <gtest/gtest.h>

namespace {
  using namespace pmc;

  YPlane tplane(4.0, Surface::BoundaryType::Transparent, 1);

  TEST(YPlane, sign) {
    Position r(1.0, 2.3, 4.0);
    Position r2(1.0, 4.5, 1.8);
    Position r3(1.2, 4.0, 0.0);
    Direction u1(0.2, 3.9, 4.2);
    Direction u2(3.4, -2.4, 1.0);

    EXPECT_EQ(tplane.sign(r,u1), Surface::Side::Negative);
    EXPECT_EQ(tplane.sign(r2,u1), Surface::Side::Positive);
    EXPECT_EQ(tplane.sign(r3,u1), Surface::Side::Positive);
    EXPECT_EQ(tplane.sign(r3, u2), Surface::Side::Negative);
  }

  TEST(YPlane, distance) {
    Position r1(1.0,2.0,0.0);
    Direction u1(0.0,1.0,0.0);

    Position r2(0.3, 4.5, 2.2);
    Direction u2(0.0, -1.0, 0.0);

    Direction u3(1.0, 0.0, 0.0);
    Direction u4(0.1, 0.1, 0.1);

    EXPECT_DOUBLE_EQ(4.0-r1.y(), tplane.distance(r1,u1));
    EXPECT_DOUBLE_EQ(INF, tplane.distance(r1,u2));
    EXPECT_DOUBLE_EQ(r2.y()-4.0, tplane.distance(r2,u2));
    EXPECT_DOUBLE_EQ(INF, tplane.distance(r1,u3));
    EXPECT_DOUBLE_EQ((4.0 - r1.y())/u4.y(), tplane.distance(r1,u4));
  }

  TEST(YPlane, normal) {
    Direction ypn = tplane.normal({12.,302.,32});

    EXPECT_DOUBLE_EQ(0.0, ypn.x());
    EXPECT_DOUBLE_EQ(1.0, ypn.y());
    EXPECT_DOUBLE_EQ(0.0, ypn.z());
  }
  
};
