#include <gtest/gtest.h>

#include "RayTests.hpp"
#include "SphereTests.hpp"
#include "geometry/Surface.hpp"

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
