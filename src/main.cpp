#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <Eigen/Dense>

#include "geometry/Ray.hpp"

using namespace std;
using namespace Eigen;

#include <gtest/gtest.h>

TEST(RayTest, DirectionIsNormal) {
  ASSERT_EQ(1.0, 2.0);
}

int main(int argc, const char** argv)
{
    int render_width  = atoi(argv[1]);
    int render_height = atoi(argv[2]);
    sf::RenderWindow window(sf::VideoMode(render_width, render_height), "My window");


    Vector3d x;

    sf::Image image;
    image.create(render_width, render_height, sf::Color(255,0,0));


    sf::Texture texture;
    texture.loadFromImage(image);

    sf::Sprite sprite;
    sprite.setTexture(texture, true);

    Ray ray(Vector3d(1,2,3));
    cout << ray << endl;

    int i = 0;
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else {
                window.clear();
                window.draw(sprite);
                window.display();
            }

            if (i < render_height * render_width) {
              int x = i % render_width;
              int y = i / render_width;
              image.setPixel(x, y, sf::Color(255,255,255));
              i++;
              texture.update(image);
            }
        }
    }

    return 0;
}
