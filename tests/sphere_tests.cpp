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
    EXPECT_EQ(s.sign(r1,u1), Side::Negative);
    EXPECT_EQ(s.sign(r2,u1), Side::Positive);

    Position r3(3.0,1.0,1.0);
    Direction u2(-1.0,0.0,0.0);
    Direction u3(1.0,0.0,0.0);
    EXPECT_EQ(s.sign(r3,u2), Side::Negative);
    EXPECT_EQ(s.sign(r3,u3), Side::Positive);
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

  TEST(Sphere, get_ray) {
    Ray r1 = s.get_ray({-2., 1., 1.},{1.,0.,0.}, Side::Negative);
    EXPECT_EQ(r1.size(), 1);
    EXPECT_DOUBLE_EQ(r1[0].first.distance, 1.);
    EXPECT_EQ(r1[0].first.surface, 1); 
    EXPECT_EQ(r1[0].first.side, Side::Positive);
    EXPECT_DOUBLE_EQ(r1[0].second.distance, 5.);
    EXPECT_EQ(r1[0].second.surface, 1);
    EXPECT_EQ(r1[0].second.side, Side::Negative);

    Ray r2 = s.get_ray({-2., 1., 1.},{1.,0.,0.}, Side::Positive);
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

    Ray r3 = s.get_ray({-2.,1.,1.}, {-1.,0.,0.}, Side::Negative);
    EXPECT_EQ(r3.size(), 0);
    
    // Check for on surface region inside
    Ray r4 = s.get_ray({3.,1.,1.},{1.,0.,0.}, Side::Negative);
    EXPECT_EQ(r4.size(), 0);
    Ray r5 = s.get_ray({3.,1.,1.},{-1.,0.,0.}, Side::Negative);
    EXPECT_EQ(r5.size(), 1);
    EXPECT_DOUBLE_EQ(r5[0].first.distance, 0.);
    EXPECT_EQ(r5[0].first.surface, 0);
    EXPECT_EQ(r5[0].first.side, Side::Positive);
    EXPECT_DOUBLE_EQ(r5[0].second.distance, 4.);
    EXPECT_EQ(r5[0].second.surface, 1);
    EXPECT_EQ(r5[0].second.side, Side::Negative);
    
    // Check on surface region outside
    Ray r6 = s.get_ray({3.,1.,1.},{1.,0.,0.}, Side::Positive);
    EXPECT_EQ(r6.size(), 1);
    EXPECT_DOUBLE_EQ(r6[0].first.distance, 0.);
    EXPECT_EQ(r6[0].first.surface, 0);
    EXPECT_EQ(r6[0].first.side, Side::Positive);
    EXPECT_DOUBLE_EQ(r6[0].second.distance, INF);
    EXPECT_EQ(r6[0].second.surface, 0);
    EXPECT_EQ(r6[0].second.side, Side::Positive);
    Ray r7 = s.get_ray({3.,1.,1.},{-1.,0.,0.}, Side::Positive);
    EXPECT_EQ(r7.size(), 1);
    EXPECT_DOUBLE_EQ(r7[0].first.distance, 4.);
    EXPECT_EQ(r7[0].first.surface, 1);
    EXPECT_EQ(r7[0].first.side, Side::Negative);
    EXPECT_DOUBLE_EQ(r7[0].second.distance, INF);
    EXPECT_EQ(r7[0].second.surface, 0);
    EXPECT_EQ(r7[0].second.side, Side::Positive);
  }
};
