#include <gtest/gtest.h>

#include "geometry/Ray.hpp"

TEST(RayTest, DefaultOriginIsWorldOrigin) {
  Ray r(Vector3d(5.0, 1.0, 0.0));

  ASSERT_EQ(r.origin(), Vector3d(0,0,0));
}

TEST(RayTest, DirectionIsUnitLength) {
  Ray r(Vector3d(5.0, 1.0, 0.0));

  ASSERT_EQ(r.direction().norm(), 1.0);
}

TEST(RayTest, RaysCanBeFlipped) {
  Ray r(Vector3d(2.0, 0.0, 0.0));

  Ray flipped = r.flipped();

  ASSERT_EQ(flipped.origin(), r.origin());
  ASSERT_EQ(flipped.direction(), -r.direction());
  ASSERT_EQ(flipped.direction(), Vector3d(-1.0, 0.0, 0.0));
}
