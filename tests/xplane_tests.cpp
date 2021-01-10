#include <Papillon/geometry/surfaces/xplane.hpp>
#include <Papillon/utils/constants.hpp>
#include <gtest/gtest.h>

namespace {
  using namespace pmc;

  XPlane tplane(3.0, Surface::BoundaryType::Transparent, 1);

  TEST(XPlane, sign) {
    Position r(1.0,2.0,3.0);
    Direction u(1.0,0.0,0.0);
    Direction u1(-1.0,0.0,0.0);

    EXPECT_EQ(tplane.sign(r,u), Side::Negative);

    Position r1(4.7, 1.0,-4.5);
    EXPECT_EQ(tplane.sign(r1,u), Side::Positive);

    Position r2(3.0,0.0,2.0);
    EXPECT_EQ(tplane.sign(r2,u), Side::Positive);
    EXPECT_EQ(tplane.sign(r2,u1), Side::Negative);
  }

  TEST(XPlane, distance) {
    Position r(1.2, 3.0, 4.0);
    Direction u(1.0, 0.0, 0.0);

    EXPECT_DOUBLE_EQ(3.0-r.x(), tplane.distance(r,u));

    Direction u2(-1.0,1.0,1.0);
    EXPECT_DOUBLE_EQ(INF, tplane.distance(r,u2));

    Direction u3(0.0,2.9,1.2);
    EXPECT_DOUBLE_EQ(INF, tplane.distance(r,u3));

    Direction u4(2.3,-1.2,1.9);
    EXPECT_DOUBLE_EQ((3.0-r.x())/u4.x(), tplane.distance(r,u4));
  }

  TEST(XPlane, normal) {
    Direction xpn = tplane.normal({0.2,3.0,1.8});
    EXPECT_DOUBLE_EQ(1.0, xpn.x());
    EXPECT_DOUBLE_EQ(0.0, xpn.y());
    EXPECT_DOUBLE_EQ(0.0, xpn.z());
  }

  TEST(XPlane, get_ray) {
    Ray r1 = tplane.get_ray({2.0,0.,0.},{1.,0.,0.},Side::Positive);
    EXPECT_EQ(r1.size(), 1);
    EXPECT_DOUBLE_EQ(r1[0].first.distance, 1.);
    EXPECT_EQ(r1[0].first.surface, 1);
    EXPECT_EQ(r1[0].first.side, Side::Negative);
    EXPECT_DOUBLE_EQ(r1[0].second.distance, INF);
    EXPECT_EQ(r1[0].second.surface, 0);
    EXPECT_EQ(r1[0].second.side, Side::Positive);

    Ray r2 = tplane.get_ray({2.0,0.,0.},{1.,0.,0.},Side::Negative);
    EXPECT_EQ(r2.size(), 1);
    EXPECT_DOUBLE_EQ(r2[0].first.distance, 0.);
    EXPECT_EQ(r2[0].first.surface, 0);
    EXPECT_EQ(r2[0].first.side, Side::Positive);
    EXPECT_DOUBLE_EQ(r2[0].second.distance, 1.);
    EXPECT_EQ(r2[0].second.surface, 1);
    EXPECT_EQ(r2[0].second.side, Side::Negative);

    Ray r3 = tplane.get_ray({2.0,0.,0.},{0.,1.,0.},Side::Positive);
    EXPECT_EQ(r3.size(), 0);

    Ray r4 = tplane.get_ray({4.0,0.,0.},{-1.,0.,0.},Side::Positive);
    EXPECT_EQ(r4.size(), 1);
    EXPECT_DOUBLE_EQ(r4[0].first.distance, 0.);
    EXPECT_EQ(r4[0].first.surface, 0);
    EXPECT_EQ(r4[0].first.side, Side::Positive);
    EXPECT_DOUBLE_EQ(r4[0].second.distance, 1.);
    EXPECT_EQ(r4[0].second.surface, 1);
    EXPECT_EQ(r4[0].second.side, Side::Positive);

    Ray r5 = tplane.get_ray({4.0,0.,0.},{-1.,0.,0.},Side::Negative);
    EXPECT_EQ(r5.size(), 1);
    EXPECT_DOUBLE_EQ(r5[0].first.distance, 1.);
    EXPECT_EQ(r5[0].first.surface, 1);
    EXPECT_EQ(r5[0].first.side, Side::Positive);
    EXPECT_DOUBLE_EQ(r5[0].second.distance, INF);
    EXPECT_EQ(r5[0].second.surface, 0);
    EXPECT_EQ(r5[0].second.side, Side::Positive);
  }
};
