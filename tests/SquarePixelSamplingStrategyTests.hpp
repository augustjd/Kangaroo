#include <gtest/gtest.h>

#include "camera/SquarePixelSamplingStrategy.hpp"
#include "camera/PixelSamplingStrategy.hpp"
#include <iostream>

#include <vector>

using namespace std;

TEST(SquarePixelSamplingStrategyTests, IteratesSquare) {
    int pixels_returned = 0;
    SquarePixelSamplingStrategy s(10,5);
    while(s.next()) {
        pixels_returned += 1;
    }

    ASSERT_EQ(pixels_returned, 50);
}

TEST(SquarePixelSamplingStrategyTests, IteratesBigSquare) {
    SquarePixelSamplingStrategy s(100, 100, 50);

    vector<Pixel> to_sample;
    for (int i = 0; i < 50 * 50; i++) {
        s.next();
    }

    ASSERT_EQ(s.next(), Pixel(51,0));

    for (int i = 0; i < 50 * 50 - 1; i++) {
        s.next();
    }

    ASSERT_EQ(s.next(), Pixel(0,51));
}
