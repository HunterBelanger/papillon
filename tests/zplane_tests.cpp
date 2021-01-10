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

    EXPECT_EQ(tplane.sign(r1,u1), Side::Negative);
    EXPECT_EQ(tplane.sign(r2, u1), Side::Positive);
    EXPECT_EQ(tplane.sign(r3,u2), Side::Negative);
    EXPECT_EQ(tplane.sign(r3,u1), Side::Positive);
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

  TEST(ZPlane, get_ray) {
    Ray r1 = tplane.get_ray({2.0,0.,2.},{0.,0.,1.}, Side::Positive);
    EXPECT_EQ(r1.size(), 1);
    EXPECT_DOUBLE_EQ(r1[0].first.distance, 1.);
    EXPECT_EQ(r1[0].first.surface, 1);
    EXPECT_EQ(r1[0].first.side, Side::Negative);
    EXPECT_DOUBLE_EQ(r1[0].second.distance, INF);
    EXPECT_EQ(r1[0].second.surface, 0);
    EXPECT_EQ(r1[0].second.side, Side::Positive);

    Ray r2 = tplane.get_ray({2.0,0.,2.},{0.,0.,1.}, Side::Negative);
    EXPECT_EQ(r2.size(), 1);
    EXPECT_DOUBLE_EQ(r2[0].first.distance, 0.);
    EXPECT_EQ(r2[0].first.surface, 0);
    EXPECT_EQ(r2[0].first.side, Side::Positive);
    EXPECT_DOUBLE_EQ(r2[0].second.distance, 1.);
    EXPECT_EQ(r2[0].second.surface, 1);
    EXPECT_EQ(r2[0].second.side, Side::Negative);

    Ray r3 = tplane.get_ray({2.0,0.,2.},{0.,1.,0.}, Side::Positive);
    EXPECT_EQ(r3.size(), 0);

    Ray r4 = tplane.get_ray({2.0,0.,4.},{0.,0.,-1.}, Side::Positive);
    EXPECT_EQ(r4.size(), 1);
    EXPECT_DOUBLE_EQ(r4[0].first.distance, 0.);
    EXPECT_EQ(r4[0].first.surface, 0);
    EXPECT_EQ(r4[0].first.side, Side::Positive);
    EXPECT_DOUBLE_EQ(r4[0].second.distance, 1.);
    EXPECT_EQ(r4[0].second.surface, 1);
    EXPECT_EQ(r4[0].second.side, Side::Positive);

    Ray r5 = tplane.get_ray({2.0,0.,4.},{0.,0.,-1.}, Side::Negative);
    EXPECT_EQ(r5.size(), 1);
    EXPECT_DOUBLE_EQ(r5[0].first.distance, 1.);
    EXPECT_EQ(r5[0].first.surface, 1);
    EXPECT_EQ(r5[0].first.side, Side::Positive);
    EXPECT_DOUBLE_EQ(r5[0].second.distance, INF);
    EXPECT_EQ(r5[0].second.surface, 0);
    EXPECT_EQ(r5[0].second.side, Side::Positive);
  }
};
