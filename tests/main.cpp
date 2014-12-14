#include <gtest/gtest.h>

#include "RayTests.hpp"
#include "SphereTests.hpp"
#include "SamplerTests.hpp"
#include "TriangleTests.hpp"
#include "SquarePixelSamplingStrategyTests.hpp"
#include "SceneLoaderTests.hpp"

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
