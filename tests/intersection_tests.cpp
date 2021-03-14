#include <Papillon/geometry/csg/intersection.hpp>
#include <Papillon/geometry/csg/half_space.hpp>
#include <Papillon/geometry/surfaces/xplane.hpp>
#include <gtest/gtest.h>

namespace {
  using namespace pmc;

  TEST(intersection, is_inside) {
    std::shared_ptr<Surface> x0 = std::make_shared<XPlane>(0., Surface::BoundaryType::Transparent, 1);
    std::shared_ptr<Surface> x2 = std::make_shared<XPlane>(2., Surface::BoundaryType::Transparent, 2);
    std::shared_ptr<Volume> px = std::make_shared<HalfSpace>(x0, Surface::Side::Positive, 1);
    std::shared_ptr<Volume> nx = std::make_shared<HalfSpace>(x2, Surface::Side::Negative, 2);
    Intersection i(px, nx, 3);

    EXPECT_TRUE(i.is_inside({0.,0.,0.},{1.,0.,0.}));
    EXPECT_FALSE(i.is_inside({0.,0.,0.},{-1.,0.,0.}));
    EXPECT_TRUE(i.is_inside({0.,0.,0.},{0.,1.,0.},1, Surface::Side::Positive));
    EXPECT_FALSE(i.is_inside({0.,0.,0.},{1.,0.,0.},1, Surface::Side::Negative));
    EXPECT_TRUE(i.is_inside({2.,0.,0.},{0.,1.,0.},2, Surface::Side::Negative));
    EXPECT_FALSE(i.is_inside({2.,0.,0.},{0.,1.,0.},2, Surface::Side::Positive));
    EXPECT_TRUE(i.is_inside({1.0,12.,-12.4},{1.,1.,1.}));
    EXPECT_FALSE(i.is_inside({-0.1,12.,-12.4},{1.,1.,1.}));
    EXPECT_FALSE(i.is_inside({2.1,12.,-12.4},{1.,1.,1.}));
  }

  TEST(intersection, get_boundary) {
    std::shared_ptr<Surface> x0 = std::make_shared<XPlane>(0., Surface::BoundaryType::Vacuum, 1);
    std::shared_ptr<Surface> x2 = std::make_shared<XPlane>(2., Surface::BoundaryType::Transparent, 2);
    std::shared_ptr<Volume> px = std::make_shared<HalfSpace>(x0, Surface::Side::Positive, 1);
    std::shared_ptr<Volume> nx = std::make_shared<HalfSpace>(x2, Surface::Side::Negative, 2);
    Intersection i(px, nx, 3);

    Position r(1.5, 0., 0.);
    Direction u1(1., 0., 0.);
    Direction u2(-1., 0., 0.);
    Direction u3(0., 1., 0.);

    auto bound1 = i.get_boundary(r, u1);
    EXPECT_EQ(bound1.surface_id, x2->id());
    EXPECT_EQ(bound1.boundary_type, x2->boundary());
    EXPECT_DOUBLE_EQ(bound1.distance, x2->distance(r, u1));
    EXPECT_EQ(bound1.current_side, x2->sign(r, u1));

    auto bound2 = i.get_boundary(r, u2);
    EXPECT_EQ(bound2.surface_id, x0->id());
    EXPECT_EQ(bound2.boundary_type, x0->boundary());
    EXPECT_DOUBLE_EQ(bound2.distance, x0->distance(r, u2));
    EXPECT_EQ(bound2.current_side, x0->sign(r, u2));

    auto bound3 = i.get_boundary(r, u3);
    EXPECT_DOUBLE_EQ(bound3.distance, INF);
  }
};
