#include <gtest/gtest.h>

#include "RayTests.hpp"
#include "SphereTests.hpp"
#include "SamplerTests.hpp"
#include "SampleTests.hpp"
#include "TriangleTests.hpp"
#include "SquarePixelSamplingStrategyTests.hpp"
#include "SceneLoaderTests.hpp"
#include "ThreadUtils.hpp"

#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
