#include <Papillon/utils/direction.hpp>
#include <gtest/gtest.h>
#include <cmath>

namespace {
  using namespace pmc;

  double a = 1.0;
  double b = 2.0;
  double c = 3.0;

  double d = 1.1;
  double e = 2.2;
  double f = 3.3;

  double g = 4.4;
  double h = 5.5;
  double i = 6.6;

  TEST(Direction, construction) {
    Direction u(a,b,c);

    EXPECT_DOUBLE_EQ(1.0, u.norm());
  }

  TEST(Direction, addition) {
    Direction p1(a,b,c);    
    Direction p2(d,e,f);
    Vector v(g,h,i);

    Vector pp = p1 + p2;
    Vector vp = p1 + v;
    Vector pv = v + p1;

    EXPECT_DOUBLE_EQ(p1.x()+p2.x(), pp.x());
    EXPECT_DOUBLE_EQ(p1.y()+p2.y(), pp.y());
    EXPECT_DOUBLE_EQ(p1.z()+p2.z(), pp.z());

    EXPECT_DOUBLE_EQ(p1.x()+v.x(), vp.x());
    EXPECT_DOUBLE_EQ(p1.y()+v.y(), vp.y());
    EXPECT_DOUBLE_EQ(p1.z()+v.z(), vp.z());

    EXPECT_DOUBLE_EQ(p1.x()+v.x(), pv.x());
    EXPECT_DOUBLE_EQ(p1.y()+v.y(), pv.y());
    EXPECT_DOUBLE_EQ(p1.z()+v.z(), pv.z());
  }

  TEST(Direction, subtraction) {
    Direction p1(a,b,c);    
    Direction p2(d,e,f);
    Vector v(g,h,i);

    Vector pp = p1 - p2;
    Vector vp = p1 - v;
    Vector pv = v - p1;

    EXPECT_DOUBLE_EQ(p1.x()-p2.x(), pp.x());
    EXPECT_DOUBLE_EQ(p1.y()-p2.y(), pp.y());
    EXPECT_DOUBLE_EQ(p1.z()-p2.z(), pp.z());

    EXPECT_DOUBLE_EQ(p1.x()-v.x(), vp.x());
    EXPECT_DOUBLE_EQ(p1.y()-v.y(), vp.y());
    EXPECT_DOUBLE_EQ(p1.z()-v.z(), vp.z());

    EXPECT_DOUBLE_EQ(-(p1.x()-v.x()), pv.x());
    EXPECT_DOUBLE_EQ(-(p1.y()-v.y()), pv.y());
    EXPECT_DOUBLE_EQ(-(p1.z()-v.z()), pv.z());
  }

  TEST(Direction, dot) {
    Direction p1(a,b,c);    
    Direction p2(d,e,f);
    Vector v(g,h,i);

    double pp = p1.x()*p2.x() + p1.y()*p2.y() + p1.z()*p2.z();
    double vp = v.x()*p2.x() + v.y()*p2.y() + v.z()*p2.z();
    double pv = p1.x()*v.x() + p1.y()*v.y() + p1.z()*v.z();

    EXPECT_DOUBLE_EQ(p1*p2, pp);
    EXPECT_DOUBLE_EQ(p1.dot(p2), pp);
    EXPECT_DOUBLE_EQ(p2.dot(p1), pp);

    EXPECT_DOUBLE_EQ(v*p2, vp);
    EXPECT_DOUBLE_EQ(p2*v, vp);
    EXPECT_DOUBLE_EQ(v.dot(p2), vp);

    EXPECT_DOUBLE_EQ(p1*v, pv);
    EXPECT_DOUBLE_EQ(p1.dot(v), pv);
  }

  TEST(Direction, scale) {
    Direction p(a,b,c);    
    double sc = 2.7;
    Vector p2 = sc*p;

    EXPECT_DOUBLE_EQ(p.x()*sc, p2.x());
    EXPECT_DOUBLE_EQ(p.y()*sc, p2.y());
    EXPECT_DOUBLE_EQ(p.z()*sc, p2.z());
  }
};
