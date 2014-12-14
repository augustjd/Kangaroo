#include <gtest/gtest.h>

#include "scene/Scene.hpp"
#include "scene/SceneLoader.hpp"
#include "geometry/Sphere.hpp"

#include <iostream>

using namespace std;

TEST(SceneLoaderTests, SceneLoadsFromString) {
    unique_ptr<Scene> scene = SceneLoader::load_from_string(
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
            "<scene>"
            "<sphere r=\"3\">"
                "<position x=\"0\" y=\"0\" z=\"0\">"
                "</position>"
            "</sphere>"
            "</scene>"
            " ");

    ASSERT_EQ(scene->objects().size(), 1);
    cout << *scene << endl;
}

TEST(SceneLoaderTests, TriangleLoadsFromString) {
    unique_ptr<Scene> scene = SceneLoader::load_from_string(
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
            "<scene>"
            "<triangle r=\"3\">"
                "<point x=\"0\" y=\"0\" z=\"0\"></point>"
                "<point x=\"10\" y=\"10\" z=\"0\"></point>"
                "<point x=\"20\" y=\"30\" z=\"0\"></point>"
            "</triangle>"
            "</scene>"
            " ");

    ASSERT_EQ(scene->objects().size(), 1);
    cout << *scene << endl;
}
