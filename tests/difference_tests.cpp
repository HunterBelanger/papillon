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
    std::shared_ptr<Volume> px = std::make_shared<HalfSpace>(x0, Surface::Side::Positive, 1);
    std::shared_ptr<Volume> nx = std::make_shared<HalfSpace>(x2, Surface::Side::Negative, 2);
    std::shared_ptr<Volume> i1 = std::make_shared<Intersection>(px, nx, 3); 
    std::shared_ptr<Surface> x05 = std::make_shared<XPlane>(0.5, Surface::BoundaryType::Transparent, 3);
    std::shared_ptr<Surface> x15 = std::make_shared<XPlane>(1.5, Surface::BoundaryType::Transparent, 4);
    std::shared_ptr<Volume> px1 = std::make_shared<HalfSpace>(x05, Surface::Side::Positive, 4);
    std::shared_ptr<Volume> nx1 = std::make_shared<HalfSpace>(x15, Surface::Side::Negative, 5);
    std::shared_ptr<Volume> i2 = std::make_shared<Intersection>(px1, nx1, 6); 
    Difference d(i1, i2, 7);

    EXPECT_TRUE(d.is_inside({0.25,0.,0.},{1.,0.,0.}));
    EXPECT_TRUE(d.is_inside({1.75,0.,0.},{1.,0.,0.}));
    EXPECT_FALSE(d.is_inside({0.51,0.,0.},{1.,0.,0.}));
    EXPECT_FALSE(d.is_inside({1.49,0.,0.},{1.,0.,0.}));
    EXPECT_FALSE(d.is_inside({-0.1,0.,0.},{1.,0.,0.}));
    EXPECT_FALSE(d.is_inside({2.1,0.,0.},{1.,0.,0.}));
  }

  TEST(difference, get_boundary) {
    std::shared_ptr<Surface> x0 = std::make_shared<XPlane>(0., Surface::BoundaryType::Transparent, 1);
    std::shared_ptr<Surface> x2 = std::make_shared<XPlane>(2., Surface::BoundaryType::Transparent, 2);
    std::shared_ptr<Volume> px = std::make_shared<HalfSpace>(x0, Surface::Side::Positive, 1);
    std::shared_ptr<Volume> nx = std::make_shared<HalfSpace>(x2, Surface::Side::Negative, 2);
    std::shared_ptr<Volume> i1 = std::make_shared<Intersection>(px, nx, 3); 
    std::shared_ptr<Surface> x05 = std::make_shared<XPlane>(0.5, Surface::BoundaryType::Transparent, 3);
    std::shared_ptr<Surface> x15 = std::make_shared<XPlane>(1.5, Surface::BoundaryType::Transparent, 4);
    std::shared_ptr<Volume> px1 = std::make_shared<HalfSpace>(x05, Surface::Side::Positive, 4);
    std::shared_ptr<Volume> nx1 = std::make_shared<HalfSpace>(x15, Surface::Side::Negative, 5);
    std::shared_ptr<Volume> i2 = std::make_shared<Intersection>(px1, nx1, 6); 
    Difference d(i1, i2, 7);

    Position r1(1., 0., 0.); 
    Direction u1(1., 0., 0.);
    Direction u2(-1., 0., 0.);

    auto b1 = d.get_boundary(r1, u1);
    EXPECT_EQ(b1.surface_id, x15->id());
    EXPECT_EQ(b1.boundary_type, x15->boundary());
    EXPECT_DOUBLE_EQ(b1.distance, x15->distance(r1, u1));
    EXPECT_EQ(b1.current_side, x15->sign(r1, u1));

    auto b2 = d.get_boundary(r1, u2);
    EXPECT_EQ(b2.surface_id, x05->id());
    EXPECT_EQ(b2.boundary_type, x05->boundary());
    EXPECT_DOUBLE_EQ(b2.distance, x05->distance(r1, u2));
    EXPECT_EQ(b2.current_side, x05->sign(r1, u2));

    Position r2(0.25, 0., 0.);
    auto b3 = d.get_boundary(r2, u2);
    EXPECT_EQ(b3.surface_id, x0->id());
    EXPECT_EQ(b3.boundary_type, x0->boundary());
    EXPECT_DOUBLE_EQ(b3.distance, x0->distance(r2, u2));
    EXPECT_EQ(b3.current_side, x0->sign(r2, u2));
  }
};
