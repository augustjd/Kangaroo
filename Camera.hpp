#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <memory>
#include <SFML/Graphics.hpp>

#include "../Formatting.hpp"
#include "camera/PixelSamplingStrategy.hpp"
#include "scene/Scene.hpp"

using namespace std;

class Camera {
public:
    Camera(const Vector2d& size, double focal_length, sf::Image& output, shared_ptr<PixelSamplingStrategy> sampling, const Scene& scene) : 
        update_count(0),
        _scene(scene),
        _size(size), _focal_length(focal_length), _output(output),
        sample_count(output.getSize().y),
        pixel_sampler(sampling)
    {
        _texture.loadFromImage(output);
        reset_image();
        _sprite.setTexture(_texture, true);
    };

    virtual ~Camera(){};

    size_t width() { return _width; };
    size_t height() { return _height; };
    Vector3d pixel_position(size_t x, size_t y);

    size_t pixel_count() { return width() * height() ; };

    const sf::Color operator() (size_t x, size_t y) { 
        return _output.getPixel(x, y); 
    };

    sf::Color color_after_sample(size_t x, size_t y, const sf::Color& color) {
        Vector3d current = from_color((*this)(x,y));
        Vector3d sample  = from_color(color);

        size_t samples = sample_count[y][x];

        return to_color((current * samples + sample) / (samples + 1));
    }

    void make_sample() {
        Pixel p = pixel_sampler->next();
        if (p) {
            Ray r = make_ray(p);
            Intersection i = _scene.closest_intersection(r);

            cout << "Sampled " << p.x << "," << p.y << ", " << r << " producing " << i << endl;
            if (!i.isNone()) {

                sf::Color color = sf::Color::White;
                color.a *= (1.0 / i.distance());

                update_with_sample(p.x, p.y, color);
            } else {

                update_with_sample(p.x, p.y, sf::Color::Black);
            }
        }
    }

    const sf::Sprite& sprite() { return _sprite; };

private:
    Ray make_ray(Pixel& p) {
        Vector3d pixel_pos = pixel_position(p.x, p.y);
        return Ray(pixel_pos);
    }

    void reset_image() {
        for (size_t i = 0; i < height(); i++) {
            auto& row = sample_count[i];
            row = vector<size_t>(width());
            row.resize(width());
            std::fill(row.begin(), row.end(), 0);
        }
    }

    Vector3d from_color(const sf::Color& v) {
        return Vector3d(
                (double)v.r / 255.0,
                (double)v.g / 255.0,
                (double)v.b / 255.0
                );
    }
    sf::Color to_color(const Vector3d& v) {
        return sf::Color(
                (sf::Uint8)v.x() * 255.0,
                (sf::Uint8)v.y() * 255.0,
                (sf::Uint8)v.z() * 255.0
                );
    }

    size_t update_count;
    sf::Color& update_with_sample(size_t x, size_t y, const sf::Color& color) {
        sf::Color new_color = color_after_sample(x, y, color);

        _output.setPixel(x, y, new_color);
        sample_count[y][x] += 1;
        if (update_count == 100) {
            update_count = 0;
            _texture.update(_output);
        }
        update_count++;
    };

    vector<vector<size_t>> sample_count;

    Vector2d _size;
    double _width;
    double _height;

    double _focal_length;
    sf::Image& _output;
    sf::Texture _texture;
    sf::Sprite _sprite;

    const Scene& _scene;

    shared_ptr<PixelSamplingStrategy> pixel_sampler;
};

#endif /* end of include guard: __CAMERA_H__ */
