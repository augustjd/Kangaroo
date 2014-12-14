#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <Eigen/Dense>

#include "camera/Camera.hpp"
#include "scene/SceneLoader.hpp"
#include "camera/SquarePixelSamplingStrategy.hpp"

using namespace std;
using namespace Eigen;

static const size_t DEFAULT_RENDER_WIDTH = 200;
static const size_t DEFAULT_RENDER_HEIGHT = 100;

int main(int argc, const char** argv)
{
    int render_width, render_height;
    const char* scene_file;
    if (argc < 2 || argc > 4) {
        cerr << "Usage: ./scene [WIDTH] [HEIGHT] <scene_file>" << endl;
        exit(1);
    } else if (argc < 3) {
        render_width  = DEFAULT_RENDER_WIDTH;
        render_height = DEFAULT_RENDER_HEIGHT;

        scene_file = argv[1];
    } else if (argc == 4) {
        render_width  = atoi(argv[1]);
        render_height = atoi(argv[2]);

        scene_file = argv[3];
    }

    unique_ptr<Scene> scene = SceneLoader::load_from_file(scene_file);

    sf::RenderWindow window(sf::VideoMode(render_width, render_height), "Kangaroo");

    Vector3d x;

    sf::Image image;
    image.create(render_width, render_height, sf::Color(255,0,0));

    double focal_length = 5.0;
    auto pixel_sampling_strategy = make_shared<SquarePixelSamplingStrategy>(render_width, render_height);
    double ratio = ((double)render_width) / render_height;
    Camera cam(ratio, 1.0, Vector2d(render_width, render_height), focal_length, image, pixel_sampling_strategy, *scene.get());
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
