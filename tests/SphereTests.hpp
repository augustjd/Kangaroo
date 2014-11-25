#include <gtest/gtest.h>

#include "geometry/Sphere.hpp"
#include "geometry/Ray.hpp"

#include <iostream>
using namespace std;

TEST(SphereTest, SpherePropertiesMakeSense) {
  Sphere s(Vector3d(10.0,0.0,0.0), 5.0);

  ASSERT_EQ(s.center(), Vector3d(10.0, 0.0, 0.0));
  ASSERT_EQ(s.radius(), 5.0);
}

TEST(SphereTest, SphereIntersectionGivesNearest) {
  Ray hit(Vector3d(1.0, 0, 0));
  Sphere s(Vector3d(10.0,0.0,0.0), 5.0);

  Intersection hit_int = s.intersect(hit);

  ASSERT_EQ(hit_int.location(), Vector3d(5.0, 0.0, 0.0));
}

TEST(SphereTest, SphereMissingRayMisses) {
  Ray miss(Vector3d(0, 1.0, 0));
  Sphere s(Vector3d(10.0,0.0,0.0), 5.0);

  Intersection miss_int = s.intersect(miss);
  cout << miss_int.location() << endl;
  ASSERT_TRUE(miss_int.isNone());
}
