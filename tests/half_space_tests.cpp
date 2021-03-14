#include <Papillon/geometry/csg/half_space.hpp>
#include <Papillon/geometry/surfaces/xplane.hpp>
#include <Papillon/geometry/surfaces/sphere.hpp>
#include <gtest/gtest.h>

namespace {
  using namespace pmc;

  TEST(half_space, is_inside) {
    // Plane Test
    std::shared_ptr<Surface> x3 = std::make_shared<XPlane>(3.,Surface::BoundaryType::Transparent, 1); 
    HalfSpace h1(x3, Surface::Side::Positive, 1);
    EXPECT_TRUE(h1.is_inside({3.4,0.,12.},{-1.,0.,0.}));
    EXPECT_FALSE(h1.is_inside({1.0,0.,12.},{-1.,0.,0.}));
    EXPECT_TRUE(h1.is_inside({3.,0.,12.},{-1.,0.,0.}, 1, Surface::Side::Positive));
    EXPECT_FALSE(h1.is_inside({3.,0.,12.},{1.,0.,0.}, 1, Surface::Side::Negative));
    EXPECT_FALSE(h1.is_inside({3.,0.,12.},{-1.,0.,0.}));
    EXPECT_TRUE(h1.is_inside({3.,0.,12.},{1.,0.,0.}));

    // Sphere Test
    std::shared_ptr<Surface> s = std::make_shared<Sphere>(2.,2.,2.,2.,Surface::BoundaryType::Transparent, 2); 
    HalfSpace h2(s, Surface::Side::Negative, 2);
    EXPECT_TRUE(h2.is_inside({3.4,2.,2.},{-1.,0.,0.}));
    EXPECT_FALSE(h2.is_inside({4.1,2.,2.},{-1.,0.,0.}));
    EXPECT_TRUE(h2.is_inside({4.1,2.,2.},{1.,0.,0.}, 2, Surface::Side::Negative));
    EXPECT_FALSE(h2.is_inside({2.,2.,2.},{1.,0.,0.}, 2, Surface::Side::Positive));
    EXPECT_FALSE(h2.is_inside({4.,2.,2.},{1.,0.,0.}));
    EXPECT_TRUE(h2.is_inside({4.,2.,2.},{-1.,0.,0.}));
  }

  TEST(half_space, get_boundary) {
    // Plane Test
    std::shared_ptr<Surface> x3 = std::make_shared<XPlane>(3.,Surface::BoundaryType::Transparent, 1); 
    HalfSpace h1(x3, Surface::Side::Positive, 1);

    Position r(0., 0., 0.);
    Direction u(1., 0., 0.);
    Direction u1(-1., 0., 0.);

    Boundary bound = h1.get_boundary(r, u);

    EXPECT_EQ(bound.surface_id, x3->id());
    EXPECT_EQ(bound.boundary_type, x3->boundary());
    EXPECT_DOUBLE_EQ(bound.distance, x3->distance(r, u));
    EXPECT_EQ(bound.current_side, x3->sign(r, u));

    Boundary bound2 = h1.get_boundary(r, u1);
    EXPECT_EQ(bound2.surface_id, x3->id());
    EXPECT_EQ(bound2.boundary_type, x3->boundary());
    EXPECT_DOUBLE_EQ(bound2.distance, x3->distance(r, u1));
    EXPECT_EQ(bound2.current_side, x3->sign(r, u1));
  }

};
