#include <Papillon/geometry/surfaces/zplane.hpp>
#include <Papillon/utils/constants.hpp>
#include <gtest/gtest.h>

namespace {
  using namespace pmc;

  ZPlane tplane(3.0, Surface::BoundaryType::Transparent, 1);

  TEST(ZPlane, sign) {
    Position r1(1.2, 2.2, -2.8);
    Position r2(1.2, 4.5, 3.7);
    Position r3(1.2, 3.4, 3.0);
    Direction u1(0.1, 0.1, 0.1);
    Direction u2(0.1, 0.1, -0.1);

    EXPECT_EQ(tplane.sign(r1,u1), Surface::Side::Negative);
    EXPECT_EQ(tplane.sign(r2, u1), Surface::Side::Positive);
    EXPECT_EQ(tplane.sign(r3,u2), Surface::Side::Negative);
    EXPECT_EQ(tplane.sign(r3,u1), Surface::Side::Positive);
  }

  TEST(ZPlane, distance) {
    Position r1(1.2, 2.2, 2.4);
    Direction u1(0.0, 0.0, 1.0);

    Position r2(1.2, 2.2, 4.4);
    Direction u2(0.0, 0.0, -1.0);

    Position r3(12., 22, 3.0);
    Direction u3(1.1, 1.1, 1.1);
    Direction u4(1.0, 1.0, 0.0);

    EXPECT_DOUBLE_EQ(3.0 - r1.z(), tplane.distance(r1,u1));
    EXPECT_DOUBLE_EQ(r2.z() - 3.0, tplane.distance(r2,u2));
    EXPECT_DOUBLE_EQ(INF, tplane.distance(r1,u4));
    EXPECT_DOUBLE_EQ(INF, tplane.distance(r2, u1));
    EXPECT_DOUBLE_EQ((3.0 - r1.z())/u3.z(), tplane.distance(r1,u3));
  }

  TEST(ZPlane, normal) {
    Direction zpn = tplane.normal({1.2, 3.2, 4.4});

    EXPECT_DOUBLE_EQ(0.0, zpn.x());
    EXPECT_DOUBLE_EQ(0.0, zpn.y());
    EXPECT_DOUBLE_EQ(1.0, zpn.z());
  }
  
};
