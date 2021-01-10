#include <Papillon/geometry/csg/union.hpp>
#include <Papillon/geometry/csg/half_space.hpp>
#include <Papillon/geometry/surfaces/xplane.hpp>
#include <gtest/gtest.h>

namespace {
  using namespace pmc;

  TEST(Union, is_inside) {
    std::shared_ptr<Surface> x0 = std::make_shared<XPlane>(0., Surface::BoundaryType::Transparent, 1);
    std::shared_ptr<Surface> x2 = std::make_shared<XPlane>(2., Surface::BoundaryType::Transparent, 2);
    std::shared_ptr<Volume> nx = std::make_shared<HalfSpace>(x0, Side::Negative, 1);
    std::shared_ptr<Volume> px = std::make_shared<HalfSpace>(x2, Side::Positive, 2);
    Union u(px, nx, 3); 

    EXPECT_TRUE(u.is_inside({-1.,0.,0.},{1.,0.,0.}));
    EXPECT_TRUE(u.is_inside({3.,0.,0.},{1.,0.,0.}));
    EXPECT_FALSE(u.is_inside({1.,0.,0.},{1.,0.,0.}));
    EXPECT_TRUE(u.is_inside({0.,0.,0.}, {-1.,0.,0.}));
    EXPECT_FALSE(u.is_inside({0.,0.,0.}, {1.,0.,0.}));
    EXPECT_TRUE(u.is_inside({0.,0.,0.}, {-1.,0.,0.}, 1, Side::Negative));
    EXPECT_FALSE(u.is_inside({0.,0.,0.}, {1.,0.,0.}, 1, Side::Positive));
  }

  TEST(Union, ray_trace) {
    std::shared_ptr<Surface> x0 = std::make_shared<XPlane>(0., Surface::BoundaryType::Transparent, 1);
    std::shared_ptr<Surface> x2 = std::make_shared<XPlane>(2., Surface::BoundaryType::Transparent, 2);
    std::shared_ptr<Volume> nx = std::make_shared<HalfSpace>(x0, Side::Negative, 1);
    std::shared_ptr<Volume> px = std::make_shared<HalfSpace>(x2, Side::Positive, 2);
    Union u(px, nx, 3); 

    Ray r1 = u.get_ray({-1.,0.,0.}, {1.,0.,0.});
    EXPECT_EQ(r1.size(), 2);
    EXPECT_DOUBLE_EQ(r1[0].first.distance, 0.);
    EXPECT_DOUBLE_EQ(r1[0].second.distance, 1.);
    EXPECT_DOUBLE_EQ(r1[1].first.distance, 3.);
    EXPECT_DOUBLE_EQ(r1[1].second.distance, INF);

    Ray r2 = u.get_ray({1.0, 0.0, 0.0}, {-1.,0.,0.});
    EXPECT_EQ(r2.size(), 1);
    EXPECT_DOUBLE_EQ(r2[0].first.distance, 1.);
    EXPECT_DOUBLE_EQ(r2[0].second.distance, INF);
  }

};
