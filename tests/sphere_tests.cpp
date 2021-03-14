#include <Papillon/geometry/surfaces/sphere.hpp>
#include <gtest/gtest.h>

namespace {
  using namespace pmc;

  double x0 = 1.0;
  double y0 = 1.0;
  double z0 = 1.0;
  double R = 2.0;
  Sphere s(x0,y0,z0,R,Surface::BoundaryType::Transparent, 1);

  TEST(Sphere, sign) {
    Position r1(1.0,1.0,1.0);
    Position r2(3.1, 1.0, 1.0);
    Direction u1(1.0,1.0,1.0);
    EXPECT_EQ(s.sign(r1,u1), Surface::Side::Negative);
    EXPECT_EQ(s.sign(r2,u1), Surface::Side::Positive);

    Position r3(3.0,1.0,1.0);
    Direction u2(-1.0,0.0,0.0);
    Direction u3(1.0,0.0,0.0);
    EXPECT_EQ(s.sign(r3,u2), Surface::Side::Negative);
    EXPECT_EQ(s.sign(r3,u3), Surface::Side::Positive);
  }

  TEST(Sphere, distance) {
    Position r0(1.0,1.0,1.0);
    Direction u0(1.0,-23.4,32.0);
    EXPECT_DOUBLE_EQ(R, s.distance(r0,u0));

    Position r1(3.0,1.0,1.0);
    Direction u1(-1.0,0.0,0.0);
    Direction u2(1.0,1.0,1.0);
    EXPECT_DOUBLE_EQ(2.0*R, s.distance(r1, u1));
    EXPECT_DOUBLE_EQ(INF, s.distance(r1,u2));
  }

  TEST(Sphere, normal) {
    Position r0(2.0,1.0,1.0);
    Position r1(-1.0,1.0,1.0);
    Position r2(1.0,2.0,1.0);
    Position r3(1.0,-1.0,1.0);
    Position r4(1.0,1.0,2.0);
    Position r5(1.0,1.0,-1.0);

    EXPECT_DOUBLE_EQ(1.0, s.normal(r0).x());
    EXPECT_DOUBLE_EQ(-1.0, s.normal(r1).x());
    EXPECT_DOUBLE_EQ(1.0, s.normal(r2).y());
    EXPECT_DOUBLE_EQ(-1.0, s.normal(r3).y());
    EXPECT_DOUBLE_EQ(1.0, s.normal(r4).z());
    EXPECT_DOUBLE_EQ(-1.0, s.normal(r5).z());
  }

};
