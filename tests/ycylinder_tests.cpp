#include <Papillon/geometry/surfaces/ycylinder.hpp>
#include <Papillon/utils/constants.hpp>
#include <gtest/gtest.h>

namespace {
  using namespace pmc;

  double x0 = 2.0;
  double z0 = 3.0;
  double R = 2.0;
  YCylinder yc(x0, z0, R, Surface::BoundaryType::Transparent, 1);

  TEST(YCylinder, sign) {
    Position r1(2.1,0.0,3.2);
    Position r2(4.5, 0.0, 3.0);
    Position r3(4.0, 0.0, 3.0);
    Direction u1(1.0, 0.0, 1.0);
    Direction u2(-1.0, 0.0, -1.0);

    EXPECT_EQ(yc.sign(r1,u1), Surface::Side::Negative);
    EXPECT_EQ(yc.sign(r2, u1), Surface::Side::Positive);
    EXPECT_EQ(yc.sign(r3,u1), Surface::Side::Positive);
    EXPECT_EQ(yc.sign(r3, u2), Surface::Side::Negative);
  }

  TEST(YCylinder, distance) {
    Position r0(2.0, 0.0, 3.0);
    Direction u0(-1.0, 0.0, 1.0);
    EXPECT_DOUBLE_EQ(R, yc.distance(r0,u0));
    EXPECT_DOUBLE_EQ(INF, yc.distance(r0,{0.0,1.0,0.0}));

    Position r1(2.0, 0.0, 6.0);
    Direction u1(0.0, 0.0, -1.0);
    EXPECT_DOUBLE_EQ(1.0, yc.distance(r1,u1));

    Position r2(1.0, 0.0, 3.0);
    Direction u2(-1.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(1.0, yc.distance(r2, u2));
  }

  TEST(YCylinder, normal) {
    Position r0(4.0, 0.0, 3.0);
    Position r1(2.0, 0.0, 5.0);
    Position r2(0.0, 0.0, 3.0);
    Position r3(2.0, 0.0, 1.0);

    EXPECT_DOUBLE_EQ(1.0, yc.normal(r0).x());
    EXPECT_DOUBLE_EQ(1.0, yc.normal(r1).z());
    EXPECT_DOUBLE_EQ(-1.0, yc.normal(r2).x());
    EXPECT_DOUBLE_EQ(-1.0, yc.normal(r3).z());
  }
};
