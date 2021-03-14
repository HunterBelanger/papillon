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

    EXPECT_EQ(tplane.sign(r,u), Surface::Side::Negative);

    Position r1(4.7, 1.0,-4.5);
    EXPECT_EQ(tplane.sign(r1,u), Surface::Side::Positive);

    Position r2(3.0,0.0,2.0);
    EXPECT_EQ(tplane.sign(r2,u), Surface::Side::Positive);
    EXPECT_EQ(tplane.sign(r2,u1), Surface::Side::Negative);
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
  
};
