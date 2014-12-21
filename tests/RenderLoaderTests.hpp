#include <gtest/gtest.h>

#include "scene/Scene.hpp"
#include "scene/RenderLoader.hpp"
#include "geometry/Sphere.hpp"

#include <iostream>

using namespace std;

TEST(RenderLoaderTests, SceneLoadsFromString) {
    unique_ptr<Render> render = RenderLoader::load_from_string(
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
            "<render>"
            "<scene>"
            "<sphere r=\"3\">"
                "<position x=\"0\" y=\"0\" z=\"0\">"
                "</position>"
            "</sphere>"
            "</scene>"
            "</render>"
            " ");

    ASSERT_EQ(render->scene->objects().size(), 1);
}

TEST(RenderLoaderTests, TriangleLoadsFromString) {
    unique_ptr<Render> render = RenderLoader::load_from_string(
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
            "<render>"
            "<scene>"
            "<triangle r=\"3\">"
                "<point x=\"0\" y=\"0\" z=\"0\"></point>"
                "<point x=\"10\" y=\"10\" z=\"0\"></point>"
                "<point x=\"20\" y=\"30\" z=\"0\"></point>"
            "</triangle>"
            "</scene>"
            "</render>"
            " ");

    ASSERT_EQ(render->scene->objects().size(), 1);
}
