#include <Papillon/utils/vector.hpp>
#include <gtest/gtest.h>
#include <cmath>

namespace {
  using namespace pmc;

  TEST(Vector, components) {
    double x = 1.0;
    double y = 2.0;
    double z = 3.0;
    Vector v(x,y,z);

    EXPECT_DOUBLE_EQ(x, v.x());
    EXPECT_DOUBLE_EQ(y, v.y());
    EXPECT_DOUBLE_EQ(z, v.z());
  }

  TEST(Vector, dot) {
    double x = 1.0;
    double y = 2.0;
    double z = 3.0;
    double a = 1.0;
    double b = 2.0;
    double c = 3.0;
    Vector v(x,y,z);
    Vector q(a,b,c);

    double expect = x*a + y*b + z*c;

    EXPECT_DOUBLE_EQ(expect, v.dot(q));
    EXPECT_DOUBLE_EQ(expect, q.dot(v));
    EXPECT_DOUBLE_EQ(expect, v*q);
    EXPECT_DOUBLE_EQ(expect, q*v);
  }

  TEST(Vector, norm) {
    double x = 1.0;
    double y = 2.0;
    double z = 3.0;
    Vector v(x,y,z);

    double expect = std::sqrt(x*x + y*y + z*z);
    EXPECT_DOUBLE_EQ(expect, v.norm());
  }

  TEST(Vector, addition) {
    double x = 1.0;
    double y = 2.0;
    double z = 3.0;
    double a = 1.0;
    double b = 2.0;
    double c = 3.0;
    Vector v(x,y,z);
    Vector q(a,b,c);

    double exp_x = x+a;
    double exp_y = y+b;
    double exp_z = z+c;

    Vector w = v+q;

    EXPECT_DOUBLE_EQ(exp_x, w.x());
    EXPECT_DOUBLE_EQ(exp_y, w.y());
    EXPECT_DOUBLE_EQ(exp_z, w.z());
  }

  TEST(Vector, subtraction) {
    double x = 1.0;
    double y = 2.0;
    double z = 3.0;
    double a = 2.0;
    double b = 3.0;
    double c = 1.0;
    Vector v(x,y,z);
    Vector q(a,b,c);

    double exp_x = x-a;
    double exp_y = y-b;
    double exp_z = z-c;

    Vector w = v-q;

    EXPECT_DOUBLE_EQ(exp_x, w.x());
    EXPECT_DOUBLE_EQ(exp_y, w.y());
    EXPECT_DOUBLE_EQ(exp_z, w.z());
  }

  TEST(Vector, scale) {
    double x = 1.0;
    double y = 2.0;
    double z = 3.0;
    Vector v(x,y,z);
    Vector q = 2.3*v;
    Vector w = v*1.4;

    EXPECT_DOUBLE_EQ(2.3*x, q.x());
    EXPECT_DOUBLE_EQ(2.3*y, q.y());
    EXPECT_DOUBLE_EQ(2.3*z, q.z());

    EXPECT_DOUBLE_EQ(1.4*x, w.x());
    EXPECT_DOUBLE_EQ(1.4*y, w.y());
    EXPECT_DOUBLE_EQ(1.4*z, w.z());
  }
};
