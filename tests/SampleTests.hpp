#include <gtest/gtest.h>

#include "color/Sample.hpp"
#include <iostream>

using namespace std;

TEST(SampleTests, WhiteAndBlackIsGray) {
    ImportanceRay ray(Vector3d(), 1.0);

    Sample s(0,0,Color(0), ray);

    s += Color(1.0);

    sf::Color color = s.as_sfml_color();

    ASSERT_EQ(color.r, 127);
    ASSERT_EQ(color.g, 127);
    ASSERT_EQ(color.b, 127);

    s += Color(1.0);
    s += Color(1.0);
    s += Color(1.0);

    color = s.as_sfml_color();

    ASSERT_EQ(color.r, 204);
    ASSERT_EQ(color.g, 204);
    ASSERT_EQ(color.b, 204);
}
