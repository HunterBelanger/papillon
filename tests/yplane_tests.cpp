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

    EXPECT_EQ(tplane.sign(r,u1), Side::Negative);
    EXPECT_EQ(tplane.sign(r2,u1), Side::Positive);
    EXPECT_EQ(tplane.sign(r3,u1), Side::Positive);
    EXPECT_EQ(tplane.sign(r3, u2), Side::Negative);
  }

  TEST(YPlane, distance) {
    Position r1(1.0,2.0,0.0);
    Direction u1(0.0,1.0,0.0);

    Position r2(0.3, 4.5, 2.2);
    Direction u2(0.0, -1.0, 0.0);

    Direction u3(1.0, 0.0, 0.0);
    Direction u4(0.1, 0.1, 0.1);

    EXPECT_DOUBLE_EQ(4.0-r1.y(), tplane.distance(r1,u1));
    EXPECT_DOUBLE_EQ(INF, tplane.distance(r1, u2));
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

  TEST(YPlane, get_ray) {
    Ray r1 = tplane.get_ray({0.0,2.,0.},{0.,1.,0.},Side::Positive);
    EXPECT_EQ(r1.size(), 1);
    EXPECT_DOUBLE_EQ(r1[0].first.distance, 2.);
    EXPECT_EQ(r1[0].first.surface, 1);
    EXPECT_EQ(r1[0].first.side, Side::Negative);
    EXPECT_DOUBLE_EQ(r1[0].second.distance, INF);
    EXPECT_EQ(r1[0].second.surface, 0);
    EXPECT_EQ(r1[0].second.side, Side::Positive);

    Ray r2 = tplane.get_ray({2.0,2.,0.},{0.,1.,0.},Side::Negative);
    EXPECT_EQ(r2.size(), 1);
    EXPECT_DOUBLE_EQ(r2[0].first.distance, 0.);
    EXPECT_EQ(r2[0].first.surface, 0);
    EXPECT_EQ(r2[0].first.side, Side::Positive);
    EXPECT_DOUBLE_EQ(r2[0].second.distance, 2.);
    EXPECT_EQ(r2[0].second.surface, 1);
    EXPECT_EQ(r2[0].second.side, Side::Negative);

    Ray r3 = tplane.get_ray({2.0,2.,0.},{1.,0.,0.},Side::Positive);
    EXPECT_EQ(r3.size(), 0);

    Ray r4 = tplane.get_ray({0.0,6.,0.},{0.,-1.,0.},Side::Positive);
    EXPECT_EQ(r4.size(), 1);
    EXPECT_DOUBLE_EQ(r4[0].first.distance, 0.);
    EXPECT_EQ(r4[0].first.surface, 0);
    EXPECT_EQ(r4[0].first.side, Side::Positive);
    EXPECT_DOUBLE_EQ(r4[0].second.distance, 2.);
    EXPECT_EQ(r4[0].second.surface, 1);
    EXPECT_EQ(r4[0].second.side, Side::Positive);

    Ray r5 = tplane.get_ray({0.0,6.,0.},{0.,-1.,0.},Side::Negative);
    EXPECT_EQ(r5.size(), 1);
    EXPECT_DOUBLE_EQ(r5[0].first.distance, 2.);
    EXPECT_EQ(r5[0].first.surface, 1);
    EXPECT_EQ(r5[0].first.side, Side::Positive);
    EXPECT_DOUBLE_EQ(r5[0].second.distance, INF);
    EXPECT_EQ(r5[0].second.surface, 0);
    EXPECT_EQ(r5[0].second.side, Side::Positive);
  }
};
