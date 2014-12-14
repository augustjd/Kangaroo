#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <cstdlib>
#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>


#include "scene/Scene.hpp"
#include "geometry/ImportanceRay.hpp"


using namespace Eigen;
using std::vector;

class Camera {
public:
    Camera(sf::Image& image, double focal_length, const Scene& scene) :
        _image(image), _width(image.getSize().x), _height(image.getSize().y), _focal_length(focal_length), _scene(scene)
    {
        generate_rays();
    };

    virtual ~Camera() {};

    size_t width() { return _width; };
    size_t height() { return _height; };
    size_t pixels() { return _width * _height; };

    Vector3d position_of_pixel(size_t x, size_t y) {
        return Vector3d(
                (x - (_width / 2.0)),
                (y - (_height / 2.0)),
                _focal_length
                );
    }

    void sample() {
        for (size_t i = 0; i < pixels(); i++) {
            size_t x = i % _width;
            size_t y = i / _width;

            _image.setPixel(x, y, sample(rays[i]));
        }
    }
private:
    sf::Color hit_sample(ImportanceRay ray) {
        Intersection i = _scene.closest_intersection(ray);

        if (i.isNone()) {
            return sf::Color(0,0,0,255);
        } else {
            return sf::Color(255,255,255,255);
        }
    }

    sf::Color hit_sample(ImportanceRay ray) {
        Intersection i = _scene.closest_intersection(ray);

        if (i.isNone()) {
            return sf::Color(0,0,0,255);
        } else {
            return sf::Color(255,255,255,255);
        }
    }

    sf::Color depth_sample(ImportanceRay ray) {
        Intersection i = _scene.closest_intersection(ray);

        if (i.isNone()) {
            return sf::Color(0,0,0,255);
        } else {
            int val = min(255, (int)(25500 / i.distance()));
            return sf::Color(val, val, val, 255);
        }
    }


    void generate_rays() {
        rays.reserve(pixels());
        for (size_t i = 0; i < pixels(); i++) {
            rays.emplace_back(position_of_pixel(i % _width, i / _width), 1.0);
        }
    }

    sf::Image& _image;
    const Scene& _scene;

    size_t _width;
    size_t _height;

    double _focal_length;

    vector<ImportanceRay> rays;
};

#endif /* end of include guard: __CAMERA_H__ */
