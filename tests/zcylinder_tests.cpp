#include <Papillon/geometry/surfaces/zcylinder.hpp>
#include <Papillon/utils/constants.hpp>
#include <gtest/gtest.h>
#include <cmath>

namespace {
  using namespace pmc;

  double x0 = 2.0;
  double y0 = 3.0;
  double R = 2.0;
  ZCylinder zc(x0, y0, R, Surface::BoundaryType::Transparent, 1);

  TEST(ZCylinder, sign) {
    Position r1(2.1,3.2,5.0);
    Position r2(4.5, 3.0, -123.9);
    Position r3(4.0, 3.0, 0.0);
    Direction u1(1.0,1.0,0.0);
    Direction u2(-1.0,-1.0,0.0);

    EXPECT_EQ(zc.sign(r1,u1), Surface::Side::Negative);
    EXPECT_EQ(zc.sign(r2, u1), Surface::Side::Positive);
    EXPECT_EQ(zc.sign(r3, u1), Surface::Side::Positive);
    EXPECT_EQ(zc.sign(r3, u2), Surface::Side::Negative);
  }

  TEST(ZCylinder, distance) {
    Position r0(2.0, 3.0, 0.0);
    Direction u0(1.0, 1.0, 0.0);
    EXPECT_DOUBLE_EQ(R, zc.distance(r0,u0));
    EXPECT_DOUBLE_EQ(INF, zc.distance(r0,{0.,0.,1.}));

    Position r1(2.0, 6.0, 0.0);
    Direction u1(0.0, -1.0, 0.0);
    EXPECT_DOUBLE_EQ(1.0, zc.distance(r1,u1));

    Position r2(1.0, 3.0, 0.0);
    Direction u2(-1.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(1.0, zc.distance(r2,u2));
  }

  TEST(ZCylinder, normal) {
    Position r0(4.0, 3.0, 5.0);
    Position r1(2.0, 5.0, -1.4);
    Position r3(0.0, 3.0, 12.3);
    Position r4(2.0, 1.0, -13.3);

    EXPECT_DOUBLE_EQ(1.0, zc.normal(r0).x());
    EXPECT_DOUBLE_EQ(1.0, zc.normal(r1).y());
    EXPECT_DOUBLE_EQ(-1.0, zc.normal(r3).x());
    EXPECT_DOUBLE_EQ(-1.0, zc.normal(r4).y());
  }

};
