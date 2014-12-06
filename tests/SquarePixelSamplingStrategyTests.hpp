#include <gtest/gtest.h>

#include "camera/SquarePixelSamplingStrategy.hpp"
#include <iostream>

using namespace std;

TEST(SquarePixelSamplingStrategyTests, IteratesSquare) {
    int pixels_returned = 0;
    SquarePixelSamplingStrategy s(10,5);
    while(s.next()) {
        pixels_returned += 1;
    }

    ASSERT_EQ(pixels_returned, 50);
}
