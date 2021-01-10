#include <Papillon/geometry/surfaces/xcylinder.hpp>
#include <Papillon/utils/constants.hpp>
#include <gtest/gtest.h>
#include <cmath>

namespace {
  using namespace pmc;

  double z0 = 2.0;
  double y0 = 3.0;
  double R = 2.0;
  XCylinder xc(y0, z0, R, Surface::BoundaryType::Transparent, 1);

  TEST(XCylinder, sign) {
    Position r1(5.0, 3.2, 2.1);
    Position r2(-12.3, 3.0, 4.5);
    Position r3(0.0, 3.0, 4.0);
    Direction u1(0.0, 1.0, 1.0);
    Direction u2(1.0, 0.0, -1.0);

    EXPECT_EQ(xc.sign(r1, u1), Side::Negative);
    EXPECT_EQ(xc.sign(r2, u1), Side::Positive);
    EXPECT_EQ(xc.sign(r3, u1), Side::Positive);
    EXPECT_EQ(xc.sign(r3, u2), Side::Negative);
  }

  TEST(XCylinder, distance) {
    Position r0(0.0, 3.0, 2.0);
    Direction u0(0.0,1.0,1.0);
    EXPECT_DOUBLE_EQ(R, xc.distance(r0,u0));
    EXPECT_DOUBLE_EQ(INF, xc.distance(r0, {1.0,0.0,0.0}));

    Position r1(0.0, 5.1, 2.0);
    Direction u1(0.0, -1.0, 0.0);
    EXPECT_DOUBLE_EQ(r1.y() - y0 - R, xc.distance(r1,u1));

    Position r2(0.0, 3.0, 1.0);
    Direction u2(0.0, 0.0, -1.0);
    EXPECT_DOUBLE_EQ(1.0, xc.distance(r2,u2));
  }

  TEST(XCylinder, normal) {
    Position r0(0.0, 3.0, 4.0);
    Position r1(0.0, 5.0, 2.0);
    Position r2(0.0, 3.0, 0.0);
    Position r3(0.0, 1.0, 2.0);

    EXPECT_DOUBLE_EQ(1.0, xc.normal(r0).z());
    EXPECT_DOUBLE_EQ(1.0, xc.normal(r1).y());
    EXPECT_DOUBLE_EQ(-1.0, xc.normal(r2).z());
    EXPECT_DOUBLE_EQ(-1.0, xc.normal(r3).y());
  }

  TEST(XCylinder, get_ray) {
    Ray r1 = xc.get_ray({-1., 0., 2.},{0.,1.,0.}, Side::Negative);
    EXPECT_EQ(r1.size(), 1);
    EXPECT_DOUBLE_EQ(r1[0].first.distance, 1.);
    EXPECT_EQ(r1[0].first.surface, 1);
    EXPECT_EQ(r1[0].first.side, Side::Positive);
    EXPECT_DOUBLE_EQ(r1[0].second.distance, 5.);
    EXPECT_EQ(r1[0].second.surface, 1);
    EXPECT_EQ(r1[0].second.side, Side::Negative);

    Ray r2 = xc.get_ray({-1., 0., 2.},{0.,1.,0.}, Side::Positive);
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
    
    // Traveling allong cylinder. We assume on is inside in
    // this case, so should get (0, INF)
    Ray r3 = xc.get_ray({-1.,1.,2.}, {1.,0.,0.}, Side::Negative);
    EXPECT_EQ(r3.size(), 1);
    EXPECT_DOUBLE_EQ(r3[0].first.distance, 0.);
    EXPECT_EQ(r3[0].first.surface, 0);
    EXPECT_EQ(r3[0].first.side, Side::Positive);
    EXPECT_DOUBLE_EQ(r3[0].second.distance, INF);
    EXPECT_EQ(r3[0].second.surface, 0);
    EXPECT_EQ(r3[0].second.side, Side::Positive);

    Ray r4 = xc.get_ray({0.,3.,2.},{-1.,0.,0.}, Side::Negative);
    EXPECT_EQ(r4.size(), 1);
    EXPECT_DOUBLE_EQ(r4[0].first.distance, 0.);
    EXPECT_EQ(r4[0].first.surface, 0);
    EXPECT_EQ(r4[0].first.side, Side::Positive);
    EXPECT_DOUBLE_EQ(r4[0].second.distance, INF);
    EXPECT_EQ(r4[0].second.surface, 0);
    EXPECT_EQ(r4[0].second.side, Side::Positive);

    Ray r5 = xc.get_ray({0.,3.,2.}, {1.,0.,0.}, Side::Positive);
    EXPECT_EQ(r5.size(), 0);
  }
}; 
