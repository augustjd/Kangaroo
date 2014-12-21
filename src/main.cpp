#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <thread>
#include <iostream>
#include <Eigen/Dense>

#include "camera/Camera.hpp"
#include "camera/Display.hpp"
#include "scene/RenderLoader.hpp"
#include "camera/SquarePixelSamplingStrategy.hpp"

using namespace std;
using namespace Eigen;

struct MouseLocation {
    Vector2d position;
};

static MouseLocation* location = NULL;

int main(int argc, const char** argv)
{
    const char* scene_file;
    const char* output_file = NULL;
    if (argc < 2) {
        cerr << "Usage: ./scene <scene_file> <output_file>" << endl;
        exit(1);
    } else {
        scene_file = argv[1];
    }

    if (argc > 2) {
        output_file = argv[2];
    }

    unique_ptr<Render> render = RenderLoader::load_from_file(scene_file);
    cout << render->scene.get() << endl;

    sf::RenderWindow window(sf::VideoMode(render->camera->width(), render->camera->height()), "Kangaroo");

    Vector3d x;

    shared_ptr<sf::Image> image = render->camera->image();
    Display display(*image);

    thread cam_thread([&] { render->camera->sample(); });
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            render->camera->move_right(-5);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            render->camera->move_right(5);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            render->camera->move_up(5);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            render->camera->move_up(-5);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LBracket))
        {
            render->camera->move_in(-5);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RBracket))
        {
            render->camera->move_in(5);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i _position = sf::Mouse::getPosition();
            Vector2d position(_position.x, _position.y);
            if (location == NULL) {
                location = new MouseLocation { position };
            }
        } else {
            location = NULL;
        }

        window.clear();
        window.draw(display.sprite());
        window.display();

        display.update();
    }

    if (render->camera->done() && output_file != NULL) {
        image->saveToFile(output_file);
    }

    return 0;
}
