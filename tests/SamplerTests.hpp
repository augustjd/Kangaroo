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
