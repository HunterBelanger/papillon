#include <Papillon/geometry/csg/difference.hpp>
#include <Papillon/geometry/csg/intersection.hpp>
#include <Papillon/geometry/csg/half_space.hpp>
#include <Papillon/geometry/surfaces/xplane.hpp>
#include <gtest/gtest.h>

namespace {
  using namespace pmc;

  TEST(difference, is_inside) {
    std::shared_ptr<Surface> x0 = std::make_shared<XPlane>(0., Surface::BoundaryType::Transparent, 1);
    std::shared_ptr<Surface> x2 = std::make_shared<XPlane>(2., Surface::BoundaryType::Transparent, 2);
    std::shared_ptr<Volume> px = std::make_shared<HalfSpace>(x0, Side::Positive, 1);
    std::shared_ptr<Volume> nx = std::make_shared<HalfSpace>(x2, Side::Negative, 2);
    std::shared_ptr<Volume> i1 = std::make_shared<Intersection>(px, nx, 3); 
    std::shared_ptr<Surface> x05 = std::make_shared<XPlane>(0.5, Surface::BoundaryType::Transparent, 3);
    std::shared_ptr<Surface> x15 = std::make_shared<XPlane>(1.5, Surface::BoundaryType::Transparent, 4);
    std::shared_ptr<Volume> px1 = std::make_shared<HalfSpace>(x05, Side::Positive, 4);
    std::shared_ptr<Volume> nx1 = std::make_shared<HalfSpace>(x15, Side::Negative, 5);
    std::shared_ptr<Volume> i2 = std::make_shared<Intersection>(px1, nx1, 6); 
    Difference d(i1, i2, 7);

    EXPECT_TRUE(d.is_inside({0.25,0.,0.},{1.,0.,0.}));
    EXPECT_TRUE(d.is_inside({1.75,0.,0.},{1.,0.,0.}));
    EXPECT_FALSE(d.is_inside({0.51,0.,0.},{1.,0.,0.}));
    EXPECT_FALSE(d.is_inside({1.49,0.,0.},{1.,0.,0.}));
    EXPECT_FALSE(d.is_inside({-0.1,0.,0.},{1.,0.,0.}));
    EXPECT_FALSE(d.is_inside({2.1,0.,0.},{1.,0.,0.}));
  }

  TEST(difference, ray_trace) {
    std::shared_ptr<Surface> x0 = std::make_shared<XPlane>(0., Surface::BoundaryType::Transparent, 1);
    std::shared_ptr<Surface> x2 = std::make_shared<XPlane>(2., Surface::BoundaryType::Transparent, 2);
    std::shared_ptr<Volume> px = std::make_shared<HalfSpace>(x0, Side::Positive, 1);
    std::shared_ptr<Volume> nx = std::make_shared<HalfSpace>(x2, Side::Negative, 2);
    std::shared_ptr<Volume> i1 = std::make_shared<Intersection>(px, nx, 3); 
    std::shared_ptr<Surface> x05 = std::make_shared<XPlane>(0.5, Surface::BoundaryType::Transparent, 3);
    std::shared_ptr<Surface> x15 = std::make_shared<XPlane>(1.5, Surface::BoundaryType::Transparent, 4);
    std::shared_ptr<Volume> px1 = std::make_shared<HalfSpace>(x05, Side::Positive, 4);
    std::shared_ptr<Volume> nx1 = std::make_shared<HalfSpace>(x15, Side::Negative, 5);
    std::shared_ptr<Volume> i2 = std::make_shared<Intersection>(px1, nx1, 6); 
    Difference d(i1, i2, 7); 

    Ray r1 = d.get_ray({0.,0.,0.},{1.,0.,0.});
    EXPECT_EQ(r1.size(),2);
    EXPECT_DOUBLE_EQ(r1[0].first.distance, 0.);
    EXPECT_DOUBLE_EQ(r1[0].second.distance, 0.5);
    EXPECT_DOUBLE_EQ(r1[1].first.distance, 1.5);
    EXPECT_DOUBLE_EQ(r1[1].second.distance, 2.);
  }

};
