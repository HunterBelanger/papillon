#include <Papillon/geometry/surfaces/plane.hpp>
#include <Papillon/utils/constants.hpp>
#include <gtest/gtest.h>
#include <cmath>

namespace {
  using namespace pmc;

  double A = 1.0;
  double B = 1.0;
  double C = 1.0;
  double D = 3.0;
  Plane p(A, B, C, D, Surface::BoundaryType::Transparent, 1);

  TEST(Plane, sign) {
    Position r1(3.0, 3.0, 3.0);
    Position r2(0.0, 0.0, 0.0);
    Position r3(1.0, 1.0, 1.0);
    Direction u1(1.0, 1.0, 1.0);
    Direction u2(-1.0, -1.0, -1.0);

    EXPECT_EQ(p.sign(r1, u1), Side::Positive);
    EXPECT_EQ(p.sign(r2, u1), Side::Negative);
    EXPECT_EQ(p.sign(r3, u1), Side::Positive);
    EXPECT_EQ(p.sign(r3, u2), Side::Negative);
  }
  
  TEST(Plane, distance) {
    Position r1(2.0, 2.0, 2.0);
    Position r2(0.0, 0.0, 0.0);
    Position r3(1.0, 1.0, 1.0);
    Direction u1(1.0, 1.0, 1.0);
    Direction u2(-1.0, -1.0, -1.0);
    Direction u3(-0.5, -0.5, 1.0);

    double exp_d1 = std::sqrt(3.0);
    EXPECT_DOUBLE_EQ(exp_d1, p.distance(r1, u2));
    EXPECT_DOUBLE_EQ(INF, p.distance(r1, u1));
    EXPECT_DOUBLE_EQ(INF, p.distance(r2, u2));
    EXPECT_DOUBLE_EQ(INF, p.distance(r3, u1));
    EXPECT_DOUBLE_EQ(INF, p.distance(r1, u3));
    EXPECT_DOUBLE_EQ(exp_d1, p.distance(r2, u1));
  }

  TEST(Plane, normal) {
    Direction pn = p.normal({1.2, 2.2, 3.});

    Direction exp{A,B,C};

    EXPECT_DOUBLE_EQ(exp.x(), pn.x());
    EXPECT_DOUBLE_EQ(exp.y(), pn.y());
    EXPECT_DOUBLE_EQ(exp.z(), pn.z());
  }

  TEST(Plane, get_ray) {
    Ray r1 = p.get_ray({0.,0.,0.},{1.,0.,0.}, Side::Positive);
    EXPECT_EQ(r1.size(), 1);
    EXPECT_DOUBLE_EQ(r1[0].first.distance, 3.);
    EXPECT_EQ(r1[0].first.surface, 1);
    EXPECT_EQ(r1[0].first.side, Side::Negative);
    EXPECT_DOUBLE_EQ(r1[0].second.distance, INF);
    EXPECT_EQ(r1[0].second.surface, 0);
    EXPECT_EQ(r1[0].second.side, Side::Positive);

    Ray r2 = p.get_ray({0.0,0.,0.},{1.,0.,0.}, Side::Negative);
    EXPECT_EQ(r2.size(), 1);
    EXPECT_DOUBLE_EQ(r2[0].first.distance, 0.);
    EXPECT_EQ(r2[0].first.surface, 0);
    EXPECT_EQ(r2[0].first.side, Side::Positive);
    EXPECT_DOUBLE_EQ(r2[0].second.distance, 3.);
    EXPECT_EQ(r2[0].second.surface, 1);
    EXPECT_EQ(r2[0].second.side, Side::Negative);

    Ray r3 = p.get_ray({0.,0.,0.},{-1.,0.5,0.5}, Side::Positive);
    EXPECT_EQ(r3.size(), 0);
  }
};
