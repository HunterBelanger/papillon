#include <Papillon/geometry/csg/half_space.hpp>
#include <Papillon/geometry/surfaces/xplane.hpp>
#include <Papillon/geometry/surfaces/sphere.hpp>
#include <gtest/gtest.h>

namespace {
  using namespace pmc;

  TEST(half_space, is_inside) {
    // Plane Test
    std::shared_ptr<Surface> x3 = std::make_shared<XPlane>(3.,Surface::BoundaryType::Transparent, 1); 
    HalfSpace h1(x3, Side::Positive, 1);
    EXPECT_TRUE(h1.is_inside({3.4,0.,12.},{-1.,0.,0.}));
    EXPECT_FALSE(h1.is_inside({1.0,0.,12.},{-1.,0.,0.}));
    EXPECT_TRUE(h1.is_inside({3.,0.,12.},{-1.,0.,0.}, 1, Side::Positive));
    EXPECT_FALSE(h1.is_inside({3.,0.,12.},{1.,0.,0.}, 1, Side::Negative));
    EXPECT_FALSE(h1.is_inside({3.,0.,12.},{-1.,0.,0.}));
    EXPECT_TRUE(h1.is_inside({3.,0.,12.},{1.,0.,0.}));

    // Sphere Test
    std::shared_ptr<Surface> s = std::make_shared<Sphere>(2.,2.,2.,2.,Surface::BoundaryType::Transparent, 2); 
    HalfSpace h2(s, Side::Negative, 2);
    EXPECT_TRUE(h2.is_inside({3.4,2.,2.},{-1.,0.,0.}));
    EXPECT_FALSE(h2.is_inside({4.1,2.,2.},{-1.,0.,0.}));
    EXPECT_TRUE(h2.is_inside({4.1,2.,2.},{1.,0.,0.}, 2, Side::Negative));
    EXPECT_FALSE(h2.is_inside({2.,2.,2.},{1.,0.,0.}, 2, Side::Positive));
    EXPECT_FALSE(h2.is_inside({4.,2.,2.},{1.,0.,0.}));
    EXPECT_TRUE(h2.is_inside({4.,2.,2.},{-1.,0.,0.}));
  }

  TEST(half_space, ray_trace) {
    // Plane Test 
    std::shared_ptr<Surface> x3 = std::make_shared<XPlane>(3.,Surface::BoundaryType::Transparent, 1); 
    HalfSpace h1(x3, Side::Positive, 1);
    Ray r1 = h1.get_ray({0.,0.,0.},{1.,0.,0.});
    EXPECT_EQ(r1.size(),1);
    EXPECT_DOUBLE_EQ(r1[0].first.distance, 3.);
    EXPECT_DOUBLE_EQ(r1[0].second.distance, INF);
    Ray r2 = h1.get_ray({0.,0.,0.},{-1.,0.,0.});
    EXPECT_EQ(r2.size(),0);

    // Sphere Test
    std::shared_ptr<Surface> s = std::make_shared<Sphere>(2.,2.,2.,2.,Surface::BoundaryType::Transparent, 2); 
    HalfSpace h2(s, Side::Positive, 2);
    Ray r3 = h2.get_ray({-1.,2.,2.},{1.,0.,0.});
    EXPECT_EQ(r3.size(),2);
    EXPECT_DOUBLE_EQ(r3[0].first.distance, 0.);
    EXPECT_DOUBLE_EQ(r3[0].second.distance, 1.);
    EXPECT_DOUBLE_EQ(r3[1].first.distance, 5.);
    EXPECT_DOUBLE_EQ(r3[1].second.distance, INF);
  }

};
