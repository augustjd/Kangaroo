#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <Eigen/Dense>

#include "geometry/Ray.hpp"
#include "camera/Camera.hpp"
#include "sampling/Sampler.hpp"

#include "camera/SquarePixelSamplingStrategy.hpp"

using namespace std;
using namespace Eigen;

static const size_t DEFAULT_RENDER_WIDTH = 800;
static const size_t DEFAULT_RENDER_HEIGHT = 600;

int main(int argc, const char** argv)
{
    int render_width, render_height;
    if (argc < 3) {
        render_width  = DEFAULT_RENDER_WIDTH;
        render_height = DEFAULT_RENDER_HEIGHT;
    } else {
        render_width  = atoi(argv[1]);
        render_height = atoi(argv[2]);
    }

    sf::RenderWindow window(sf::VideoMode(render_width, render_height), "Kangaroo");

    Vector3d x;

    sf::Image image;
    image.create(render_width, render_height, sf::Color(255,0,0));

    double focal_length = 1.0;
    auto pixel_sampling_strategy = make_shared<SquarePixelSamplingStrategy>(render_width, render_height);
    Camera cam(Vector2d(render_width, render_height), focal_length, image, pixel_sampling_strategy);
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        window.clear();
        window.draw(cam.sprite());
        window.display();

        cam.make_sample();
    }

    return 0;
}
