#include <Papillon/geometry/csg/intersection.hpp>
#include <Papillon/geometry/csg/half_space.hpp>
#include <Papillon/geometry/surfaces/xplane.hpp>
#include <gtest/gtest.h>

namespace {
  using namespace pmc;

  TEST(intersection, is_inside) {
    std::shared_ptr<Surface> x0 = std::make_shared<XPlane>(0., Surface::BoundaryType::Transparent, 1);
    std::shared_ptr<Surface> x2 = std::make_shared<XPlane>(2., Surface::BoundaryType::Transparent, 2);
    std::shared_ptr<Volume> px = std::make_shared<HalfSpace>(x0, Side::Positive, 1);
    std::shared_ptr<Volume> nx = std::make_shared<HalfSpace>(x2, Side::Negative, 2);
    Intersection i(px, nx, 3);

    EXPECT_TRUE(i.is_inside({0.,0.,0.},{1.,0.,0.}));
    EXPECT_FALSE(i.is_inside({0.,0.,0.},{-1.,0.,0.}));
    EXPECT_TRUE(i.is_inside({0.,0.,0.},{0.,1.,0.},1, Side::Positive));
    EXPECT_FALSE(i.is_inside({0.,0.,0.},{1.,0.,0.},1, Side::Negative));
    EXPECT_TRUE(i.is_inside({2.,0.,0.},{0.,1.,0.},2, Side::Negative));
    EXPECT_FALSE(i.is_inside({2.,0.,0.},{0.,1.,0.},2, Side::Positive));
    EXPECT_TRUE(i.is_inside({1.0,12.,-12.4},{1.,1.,1.}));
    EXPECT_FALSE(i.is_inside({-0.1,12.,-12.4},{1.,1.,1.}));
    EXPECT_FALSE(i.is_inside({2.1,12.,-12.4},{1.,1.,1.}));
  }

  TEST(intersection, ray_trace) {
    std::shared_ptr<Surface> x0 = std::make_shared<XPlane>(0., Surface::BoundaryType::Transparent, 1);
    std::shared_ptr<Surface> x2 = std::make_shared<XPlane>(2., Surface::BoundaryType::Transparent, 2);
    std::shared_ptr<Volume> px = std::make_shared<HalfSpace>(x0, Side::Positive, 1);
    std::shared_ptr<Volume> nx = std::make_shared<HalfSpace>(x2, Side::Negative, 2);
    Intersection i(px, nx, 3);

    Ray r1 = i.get_ray({0.,0.,0.},{1.,0.,0.});
    EXPECT_EQ(r1.size(),1);
    EXPECT_DOUBLE_EQ(r1[0].first.distance, 0.);
    EXPECT_DOUBLE_EQ(r1[0].second.distance, 2.);

    Ray r2 = i.get_ray({3.,0.,0.},{-1.,0.,0.});
    EXPECT_EQ(r2.size(), 1);
    EXPECT_DOUBLE_EQ(r2[0].first.distance, 1.);
    EXPECT_DOUBLE_EQ(r2[0].second.distance, 3.);

    Ray r3 = i.get_ray({2.,0.,0.},{1.,0.,0.});
    EXPECT_EQ(r3.size(), 0);
  }

};
