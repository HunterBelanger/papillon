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

    EXPECT_EQ(yc.sign(r1,u1), Side::Negative);
    EXPECT_EQ(yc.sign(r2, u1), Side::Positive);
    EXPECT_EQ(yc.sign(r3,u1), Side::Positive);
    EXPECT_EQ(yc.sign(r3, u2), Side::Negative);
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

  TEST(YCylinder, get_ray) {
    Ray r1 = yc.get_ray({2., 0., 0.},{0.,0.,1.}, Side::Negative);
    EXPECT_EQ(r1.size(), 1);
    EXPECT_DOUBLE_EQ(r1[0].first.distance, 1.);
    EXPECT_EQ(r1[0].first.surface, 1);
    EXPECT_EQ(r1[0].first.side, Side::Positive);
    EXPECT_DOUBLE_EQ(r1[0].second.distance, 5.);
    EXPECT_EQ(r1[0].second.surface, 1);
    EXPECT_EQ(r1[0].second.side, Side::Negative);

    Ray r2 = yc.get_ray({2., 0., 0.},{0.,0.,1.}, Side::Positive);
    EXPECT_EQ(r2.size(), 2);
    EXPECT_DOUBLE_EQ(r2[0].first.distance, 0.);
    EXPECT_EQ(r2[0].first.surface, 0);
    EXPECT_EQ(r2[0].first.side, Side::Positive);
    EXPECT_DOUBLE_EQ(r2[0].second.distance, 1.);
    EXPECT_EQ(r2[0].second.surface, 1);
    EXPECT_EQ(r2[0].second.side, Side::Positive);
    EXPECT_DOUBLE_EQ(r2[1].first.distance, 5.);
    EXPECT_EQ(r2[1].first.surface, 1);
    EXPECT_EQ(r2[1].first.side, Side::Negative);
    EXPECT_DOUBLE_EQ(r2[1].second.distance, INF);
    EXPECT_EQ(r2[1].second.surface, 0);
    EXPECT_EQ(r2[1].second.side, Side::Positive);

    Ray r3 = yc.get_ray({4.,0.,0.}, {1.,0.,0.}, Side::Negative);
    EXPECT_EQ(r3.size(), 0);

    Ray r4 = yc.get_ray({2.,3.,3.},{0.,1.,0.}, Side::Negative);
    EXPECT_EQ(r4.size(), 1);
    EXPECT_DOUBLE_EQ(r4[0].first.distance, 0.);
    EXPECT_EQ(r4[0].first.surface, 0);
    EXPECT_EQ(r4[0].first.side, Side::Positive);
    EXPECT_DOUBLE_EQ(r4[0].second.distance, INF);
    EXPECT_EQ(r4[0].second.surface, 0);
    EXPECT_EQ(r4[0].second.side, Side::Positive);

    Ray r5 = yc.get_ray({2.,3.,3.}, {0.,1.,0.}, Side::Positive);
    EXPECT_EQ(r5.size(), 0);
  }
};
