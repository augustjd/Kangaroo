#include <gtest/gtest.h>

#include "../src/geometry/Triangle.hpp"
#include "../src/geometry/Ray.hpp"
#include <Eigen/Dense>

#include <iostream>

using namespace std;
using namespace Eigen;

#define TriangleTest(name) TEST(TriangleTest, name)

TriangleTest(TrianglePrintFormatting) {
  const Triangle t(Vector3d(1.0, 0, 0), Vector3d(2, 0, 0), Vector3d(1, 1, 0));
  //cout << t << endl;
}

TriangleTest(Normal) {
  const Triangle t(Vector3d(1.0, 0, 0), Vector3d(0, 0, 0), Vector3d(0, 1, 0));

  ASSERT_EQ(t.normal(), Vector3d(0,0,1.0));
}
TriangleTest(Area) {
  const Triangle t(Vector3d(1.0, 0, 0), Vector3d(0, 0, 0), Vector3d(0, 1, 0));

  ASSERT_EQ(t.area(), 0.50);
}

TriangleTest(IntersectionIsCorrectlyNone) {
  const Triangle t(Vector3d(1.0, 0, 1.0), Vector3d(0, 0, 1.0), Vector3d(0, 1, 1.0));

  // backwards
  Ray miss(Vector3d(0,0,-1.0));

  Intersection i = t.intersect(miss);
  ASSERT_TRUE(i.isNone());

  // miss to the side
  Ray miss2(Vector3d(3,0,1.0));
  Intersection i2 = t.intersect(miss2);
  ASSERT_TRUE(i2.isNone());
}

TriangleTest(IntersectionIsCorrectlyHit) {
  const Triangle t(Vector3d(1.0, 0, 1.0), Vector3d(0, 0, 1.0), Vector3d(0, 1, 1.0));
  Ray hit(Vector3d(0,0,1.0));
  Intersection i = t.intersect(hit);

  ASSERT_FALSE(i.isNone());
  ASSERT_EQ(&i.surface(), &t);
  ASSERT_EQ(i.location(), Vector3d(0,0,1.0));

  Ray hit2(Vector3d(0.1,0,1.0));
  Intersection i2 = t.intersect(hit2);

  ASSERT_FALSE(i2.isNone());
  ASSERT_EQ(&i2.surface(), &t);
  ASSERT_EQ(i2.location(), Vector3d(0.1,0,1.0));
}
