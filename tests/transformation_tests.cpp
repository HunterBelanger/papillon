#include <Papillon/utils/transformation.hpp>
#include <gtest/gtest.h>

namespace {
  using namespace pmc;

  TEST(Transformation, translation) {
    Transformation t1 = Transformation::translation(1,2,3);
    Vector v1(0., 0., 0.);
    Vector t1_v1 = t1 * v1;
    EXPECT_DOUBLE_EQ(t1_v1[0], 1.);
    EXPECT_DOUBLE_EQ(t1_v1[1], 2.);
    EXPECT_DOUBLE_EQ(t1_v1[2], 3.);

    Transformation t2 = Transformation::translation(-1*t1_v1);
    Vector t2_v1 = t2 * v1;
    EXPECT_DOUBLE_EQ(t2_v1[0], -1.);
    EXPECT_DOUBLE_EQ(t2_v1[1], -2.);
    EXPECT_DOUBLE_EQ(t2_v1[2], -3.);
  }

  TEST(Transformation, rotations) {
    Transformation rx = Transformation::rotation_x(PI / 2.);
    Vector v1(0., 1., 0.);
    Vector rx_v1 = rx * v1;
    EXPECT_NEAR(rx_v1[0], 0., 1.E-16);
    EXPECT_NEAR(rx_v1[1], 0., 1.E-16);
    EXPECT_NEAR(rx_v1[2], 1., 1.E-16);

    Transformation ry = Transformation::rotation_y(PI / 2.);
    Vector v2(1., 0., 0.);
    Vector ry_v2 = ry * v2;
    EXPECT_NEAR(ry_v2[0], 0., 1.E-16);
    EXPECT_NEAR(ry_v2[1], 0., 1.E-16);
    EXPECT_NEAR(ry_v2[2], -1., 1.E-16);

    Transformation rz = Transformation::rotation_z(PI / 2.);
    Vector v3(1., 0., 0.);
    Vector rz_v3 = rz * v3;
    EXPECT_NEAR(rz_v3[0], 0., 1.E-16);
    EXPECT_NEAR(rz_v3[1], 1., 1.E-16);
    EXPECT_NEAR(rz_v3[2], 0., 1.E-16);
  }

  TEST(Transformation, scales) {
    Transformation s3 = Transformation::scale(3.);
    Vector v(1., 1., 1.);

    Vector s3_v = s3 * v;
    EXPECT_NEAR(s3_v[0], 3., 1.E-16);
    EXPECT_NEAR(s3_v[1], 3., 1.E-16);
    EXPECT_NEAR(s3_v[2], 3., 1.E-16);

    Transformation sx2 = Transformation::scale_x(2.);
    Vector sx2_v = sx2 * v;
    EXPECT_NEAR(sx2_v[0], 2., 1.E-16);
    EXPECT_NEAR(sx2_v[1], 1., 1.E-16);
    EXPECT_NEAR(sx2_v[2], 1., 1.E-16);

    Transformation sy5 = Transformation::scale_y(5.);
    Vector sy5_v = sy5 * v;
    EXPECT_NEAR(sy5_v[0], 1., 1.E-16);
    EXPECT_NEAR(sy5_v[1], 5., 1.E-16);
    EXPECT_NEAR(sy5_v[2], 1., 1.E-16);

    Transformation sz6 = Transformation::scale_z(6.);
    Vector sz6_v = sz6 * v;
    EXPECT_NEAR(sz6_v[0], 1., 1.E-16);
    EXPECT_NEAR(sz6_v[1], 1., 1.E-16);
    EXPECT_NEAR(sz6_v[2], 6., 1.E-16);
  }

  TEST(Transformation, inverse) {
    Transformation rx = Transformation::rotation_x(PI / 2.);
    Transformation ry = Transformation::rotation_y(PI / 2.);
    Transformation rz = Transformation::rotation_z(PI / 2.);
    Transformation r = rz * ry * rx;

    Vector v(1,2,3);

    Vector rv = r * v;

    Vector r_i_r_v = r.inverse()*rv;

    EXPECT_NEAR(r_i_r_v[0], v[0], 1.E-16);
    EXPECT_NEAR(r_i_r_v[1], v[1], 1.E-16);
    EXPECT_NEAR(r_i_r_v[2], v[2], 1.E-16);
  }

  TEST(Transformation, direction_mult) {
    Transformation rx = Transformation::rotation_x(PI / 2.);
    Transformation ry = Transformation::rotation_y(PI / 2.);
    Transformation rz = Transformation::rotation_z(PI / 2.);
    Transformation r = rz * ry * rx;

    Vector v1(1., 2., 3.);
    Vector v2(5., 6., 7.);
    Direction u12 = v2 - v1;

    Vector rv1 = r * v1;
    Vector rv2 = r * v2;
    Direction ur12 = rv2 - rv1;
    Direction ru12 = r * u12;

    EXPECT_NEAR(ur12[0], ru12[0], 1.E-16);
    EXPECT_NEAR(ur12[1], ru12[1], 1.E-16);
    EXPECT_NEAR(ur12[2], ru12[2], 1.E-16);
  }

  TEST(Transformation, transformation_mult) {
    Transformation rx = Transformation::rotation_x(PI / 2.);
    Transformation ry = Transformation::rotation_y(PI / 2.);
    Transformation rz = Transformation::rotation_z(PI / 2.);
    Transformation r = rz * ry * rx;

    Vector v(0., 1., 0.);
    Vector rv = r * v;

    EXPECT_NEAR(v[0], rv[0], 1.E-16);
    EXPECT_NEAR(v[1], rv[1], 1.E-16);
    EXPECT_NEAR(v[2], rv[2], 1.E-16);
  }

}