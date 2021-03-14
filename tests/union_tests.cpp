#include <Papillon/geometry/csg/union.hpp>
#include <Papillon/geometry/csg/half_space.hpp>
#include <Papillon/geometry/surfaces/xplane.hpp>
#include <gtest/gtest.h>

namespace {
  using namespace pmc;

  TEST(Union, is_inside) {
    std::shared_ptr<Surface> x0 = std::make_shared<XPlane>(0., Surface::BoundaryType::Transparent, 1);
    std::shared_ptr<Surface> x2 = std::make_shared<XPlane>(2., Surface::BoundaryType::Transparent, 2);
    std::shared_ptr<Volume> nx = std::make_shared<HalfSpace>(x0, Surface::Side::Negative, 1);
    std::shared_ptr<Volume> px = std::make_shared<HalfSpace>(x2, Surface::Side::Positive, 2);
    Union u(px, nx, 3); 

    EXPECT_TRUE(u.is_inside({-1.,0.,0.},{1.,0.,0.}));
    EXPECT_TRUE(u.is_inside({3.,0.,0.},{1.,0.,0.}));
    EXPECT_FALSE(u.is_inside({1.,0.,0.},{1.,0.,0.}));
    EXPECT_TRUE(u.is_inside({0.,0.,0.}, {-1.,0.,0.}));
    EXPECT_FALSE(u.is_inside({0.,0.,0.}, {1.,0.,0.}));
    EXPECT_TRUE(u.is_inside({0.,0.,0.}, {-1.,0.,0.}, 1, Surface::Side::Negative));
    EXPECT_FALSE(u.is_inside({0.,0.,0.}, {1.,0.,0.}, 1, Surface::Side::Positive));
  }

  TEST(Union, get_boundary) {
    std::shared_ptr<Surface> x0 = std::make_shared<XPlane>(0., Surface::BoundaryType::Vacuum, 1);
    std::shared_ptr<Surface> x2 = std::make_shared<XPlane>(2., Surface::BoundaryType::Transparent, 2);
    std::shared_ptr<Volume> nx = std::make_shared<HalfSpace>(x0, Surface::Side::Negative, 1);
    std::shared_ptr<Volume> px = std::make_shared<HalfSpace>(x2, Surface::Side::Positive, 2);
    Union u(px, nx, 3);

    Position r1(2.5, 0., 0.);
    Position r2(1., 0., 0.);
    Direction u1(-1., 0., 0.);

    auto bound1 = u.get_boundary(r1, u1);
    EXPECT_EQ(bound1.surface_id, x2->id());
    EXPECT_EQ(bound1.boundary_type, x2->boundary());
    EXPECT_DOUBLE_EQ(bound1.distance, x2->distance(r1, u1));
    EXPECT_EQ(bound1.current_side, x2->sign(r1, u1));

    auto bound2 = u.get_boundary(r2, u1);
    EXPECT_EQ(bound2.surface_id, x0->id());
    EXPECT_EQ(bound2.boundary_type, x0->boundary());
    EXPECT_DOUBLE_EQ(bound2.distance, x0->distance(r2, u1));
    EXPECT_EQ(bound2.current_side, x0->sign(r2, u1));
  }
};
