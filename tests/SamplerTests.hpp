#include <gtest/gtest.h>

#include "sampling/Sampler.hpp"
#include <iostream>

using namespace std;

TEST(SamplerTest, ConstructorDestructorWork) {
  Sampler s;
}

TEST(SamplerTest, DifferentEachTime) {
  Sampler s;

  ASSERT_NE(s.random(), s.random());
}

TEST(SamplerTest, SeedCanBeSpecified) {
  Sampler s1(0);
  Sampler s2(0);

  ASSERT_EQ(s1.random(), s2.random());
}

TEST(SamplerTest, DoubleBetweenZeroAndOne) {
  Sampler s;
  ASSERT_LT(s.random(), 1.0);
  ASSERT_GE(s.random(), 0.0);
}

TEST(SamplerTest, RandomDirection) {
  Sampler s;

  ASSERT_EQ(s.random_direction().norm(), 1.0);
}

TEST(SamplerTest, AlignVectorsMatrixTest) {
    Vector3d x(1, 0, 0);
    Vector3d y(0, 1, 0);

    ASSERT_GT(y.dot(Geometry::align_vectors_matrix(x,y) * x), .999);
}

TEST(SamplerTest, RandomDirectionAlongPoleWorks) {
    Sampler s;

    for (int i = 0; i < 100; i++) {
        Vector3d random = s.random_direction_in_hemisphere(Vector3d(1.0, 0, 0.0));
        ASSERT_GE(random.x(), 0);
        ASSERT_LE(fabs(random.norm()- 1.0), 0.000001);
    }

    for (int i = 0; i < 10; i++) {
        Vector3d axis = s.random_direction();
        for (int j = 0; j < 100; j++) {
            Vector3d direction = s.random_direction_in_hemisphere(axis);
            ASSERT_GE(direction.dot(axis), 0.0);
        }
    }
}
