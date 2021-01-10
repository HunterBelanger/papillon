#include <Papillon/geometry/ray.hpp>
#include <gtest/gtest.h>

namespace {
  using namespace pmc;

  TEST(Ray, size) {
    Ray r1({1.,1}, {3.4,2});

    EXPECT_EQ(r1.size(), 1);

    Ray r2({{{0.,0},{2.,1}},{{2.4,2},{3.,3}},{{3.5,4},{8.,4}}});
    EXPECT_EQ(r2.size(), 3);
  }

  TEST(Ray, indexing) {
    Ray r2({{{0.,0},{2.,1}},{{2.4,2},{3.,3}},{{3.5,4},{8.,5}}});

    Ray::Segment seg = r2[0];
    EXPECT_DOUBLE_EQ(seg.first.distance,0.);
    EXPECT_EQ(seg.first.surface, 0);
    EXPECT_DOUBLE_EQ(seg.second.distance,2.);
    EXPECT_EQ(seg.second.surface, 1);

    seg = r2[1];
    EXPECT_DOUBLE_EQ(seg.first.distance, 2.4);
    EXPECT_EQ(seg.first.surface, 2);
    EXPECT_DOUBLE_EQ(seg.second.distance, 3.);
    EXPECT_EQ(seg.second.surface, 3);

    seg = r2[2];
    EXPECT_DOUBLE_EQ(seg.first.distance, 3.5);
    EXPECT_EQ(seg.first.surface, 4);
    EXPECT_DOUBLE_EQ(seg.second.distance, 8.);
    EXPECT_EQ(seg.second.surface, 5);
  }

  TEST(Ray, get_intersection) {
    Ray r1({{{0.,0},{1.,1}},{{2.,2},{3.,3}}});
    Ray r2({0.5,4}, {2.5,5});
    Ray r3 = r1.get_intersection(r2);
    EXPECT_EQ(r3.size(), 2);
    EXPECT_DOUBLE_EQ(r3[0].first.distance , 0.5);
    EXPECT_EQ(r3[0].first.surface, 4);
    EXPECT_DOUBLE_EQ(r3[0].second.distance , 1.);
    EXPECT_EQ(r3[0].second.surface, 1);
    EXPECT_DOUBLE_EQ(r3[1].first.distance , 2.);
    EXPECT_EQ(r3[1].first.surface, 2);
    EXPECT_DOUBLE_EQ(r3[1].second.distance , 2.5);
    EXPECT_EQ(r3[1].second.surface, 5);

    Ray r3_2 = r2.get_intersection(r1);
    EXPECT_EQ(r3_2.size(), 2);
    EXPECT_DOUBLE_EQ(r3_2[0].first.distance , 0.5);
    EXPECT_EQ(r3_2[0].first.surface, 4);
    EXPECT_DOUBLE_EQ(r3_2[0].second.distance , 1.);
    EXPECT_EQ(r3_2[0].second.surface, 1);
    EXPECT_DOUBLE_EQ(r3_2[1].first.distance , 2.);
    EXPECT_EQ(r3_2[1].first.surface, 2);
    EXPECT_DOUBLE_EQ(r3_2[1].second.distance , 2.5);
    EXPECT_EQ(r3_2[1].second.surface, 5);

    Ray r4({2.3,0}, {3.0,0});
    Ray r5({3.2,0}, {4.8,0});
    Ray r6 = r4.get_intersection(r5);
    EXPECT_EQ(r6.size(), 0);
  }

  TEST(Ray, get_union) {
    Ray r1({{{0.,0},{1.,1}},{{2.,2},{3.,3}}});
    Ray r2({0.5,4}, {2.5,5});
    Ray r3 = r1.get_union(r2);
    EXPECT_EQ(r3.size(), 1);
    EXPECT_DOUBLE_EQ(r3[0].first.distance , 0.);
    EXPECT_EQ(r3[0].first.surface, 0); 
    EXPECT_DOUBLE_EQ(r3[0].second.distance , 3.);
    EXPECT_EQ(r3[0].second.surface, 3);

    Ray r3_2 = r2.get_union(r1);
    EXPECT_EQ(r3_2.size(), 1);
    EXPECT_DOUBLE_EQ(r3_2[0].first.distance , 0.);
    EXPECT_EQ(r3_2[0].first.surface, 0);
    EXPECT_DOUBLE_EQ(r3_2[0].second.distance , 3.);
    EXPECT_EQ(r3_2[0].second.surface, 3);

    Ray r4({2.3,1}, {3.0,2});
    Ray r5({3.2,3}, {4.8,4});
    Ray r6 = r4.get_union(r5);
    EXPECT_EQ(r6.size(), 2);
    EXPECT_DOUBLE_EQ(r6[0].first.distance, 2.3);
    EXPECT_EQ(r6[0].first.surface, 1);
    EXPECT_DOUBLE_EQ(r6[0].second.distance, 3.0);
    EXPECT_EQ(r6[0].second.surface, 2);
    EXPECT_DOUBLE_EQ(r6[1].first.distance , 3.2);
    EXPECT_EQ(r6[1].first.surface, 3);
    EXPECT_DOUBLE_EQ(r6[1].second.distance , 4.8);
    EXPECT_EQ(r6[1].second.surface, 4);
  }

  TEST(Ray, get_difference) {
    Ray r1({0.,0},{1.,1});
    Ray r2({0.5,2},{1.5,3});
    Ray r3 = r1.get_difference(r2);
    EXPECT_EQ(r3.size(), 1);
    EXPECT_DOUBLE_EQ(r3[0].first.distance, 0.);
    EXPECT_EQ(r3[0].first.surface, 0);
    EXPECT_DOUBLE_EQ(r3[0].second.distance, 0.5);
    EXPECT_EQ(r3[0].second.surface, 2);

    Ray r4({0.,0}, {5.,1});
    Ray r5({1.,2}, {3.,3});
    Ray r6 = r4.get_difference(r5);
    EXPECT_EQ(r6.size(), 2);
    EXPECT_DOUBLE_EQ(r6[0].first.distance, 0.);
    EXPECT_EQ(r6[0].first.surface, 0);
    EXPECT_DOUBLE_EQ(r6[0].second.distance, 1.);
    EXPECT_EQ(r6[0].second.surface, 2);
    EXPECT_DOUBLE_EQ(r6[1].first.distance, 3.);
    EXPECT_EQ(r6[1].first.surface, 3);
    EXPECT_DOUBLE_EQ(r6[1].second.distance, 5.);
    EXPECT_EQ(r6[1].second.surface, 1);

    Ray r7 = r5.get_difference(r4);
    EXPECT_EQ(r7.size(), 0);
  }

};
