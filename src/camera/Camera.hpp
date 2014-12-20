#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <cstdlib>
#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>
#include <chrono>

#include "Constants.hpp"
#include "color/Sample.hpp"
#include "scene/Scene.hpp"
#include "geometry/ImportanceRay.hpp"
#include "camera/tracer/Tracer.hpp"
#include "camera/tracer/DepthPathTracer.hpp"


using namespace Eigen;
using std::vector;

static Sampler sampler;
class Camera {
public:
    Camera(sf::Image& image, unsigned int fovx, const Scene& scene) :
        _image(image), 
        _width(image.getSize().x), 
        _up(0,1,0),
        _height(image.getSize().y), 
        _focal_length(fabs((image.getSize().x / 2.0)/tan(Constants::degrees_to_radians(fovx/2.0)))), 
        _scene(scene),
        _tracer(new DepthPathTracer(sampler, 4))
    {
        _position = Vector3d(0, 0, -_focal_length);
        _right = _position.cross(_up).normalized();
        initialize_samples();
    };

    Camera(Vector3d position, Vector3d up, sf::Image& image, unsigned int fovx, const Scene& scene) :
        _image(image), 
        _width(image.getSize().x), 
        _position(position),
        _up(up.normalized()),
        _height(image.getSize().y), 
        _focal_length(fabs((image.getSize().x / 2.0)/tan(Constants::degrees_to_radians(fovx/2.0)))), 
        _scene(scene),
        _tracer(new DepthPathTracer(sampler, 4))
    {
        _right = _position.cross(_up).normalized();
        initialize_samples();
    };

    virtual ~Camera() {};

    size_t width() { return _width; };
    size_t height() { return _height; };
    size_t pixels() { return _width * _height; };

    Vector3d position_of_pixel(size_t x, size_t y) {
        double x_rel = ((double)x - (double)(_width / 2.0));
        double y_rel = ((double)y - (double)(_height / 2.0));

        Vector3d result = _position + (_right * x_rel) + (_up * y_rel);
        result.z() += _focal_length;    
        return result;
    }

    void sample() {
        int max_passes = 30;
        std::chrono::high_resolution_clock::time_point t1, t2;
        for (int i = 0; i < max_passes; i++) {
            t1 = std::chrono::high_resolution_clock::now();
            for(Sample& s : samples) {
                s += _tracer->trace(_scene, s.ray);
                _image.setPixel(s.x, s.y, s.as_sfml_color());
            }
            t2 = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
            cout << "Finished pass " << BOLD_BLUE(i+1) << "/" << max_passes << " in " << BOLD_GREEN(duration << "ms.") << endl;
        }
        _image.saveToFile("out.png");
    }
private:
    sf::Color sample(Sample& sample) {
        Intersection i = _scene.closest_intersection(sample.ray);

        if (i.isNone()) {
            return sample.update(Color(0));
        } else {
            return sample.update(Color(255));
        }
    }

    sf::Color hit_sample(Sample& sample) {
        Intersection i = _scene.closest_intersection(sample.ray);

        if (i.isNone()) {
            return sample.update(Color(0));
        } else {
            return sample.update(Color(255));
        }
    }

    sf::Color depth_sample(Sample& sample) {
        Intersection i = _scene.closest_intersection(sample.ray);

        if (i.isNone()) {
            return sample.update(Color(0));
        } else {
            int val = min(255, (int)(25500 / i.distance()));
            return sample.update(Color(val));
        }
    }


    void initialize_samples() {
        rays.reserve(pixels());
        samples.reserve(pixels());

        for (size_t i = 0; i < pixels(); i++) {
            size_t x = i % _width;
            size_t y = i / _width;

            rays.emplace_back(position_of_pixel(x,y), (position_of_pixel(x, y) - _position).normalized(), 1.0);
            samples.emplace_back(x, y, rays[i]);
        }
    }
    Vector3d _position;
    Vector3d _up;
    Vector3d _right;

    sf::Image& _image;
    const Scene& _scene;

    size_t _width;
    size_t _height;

    double _focal_length;

    unique_ptr<Tracer> _tracer;

    vector<Sample> samples;
    vector<ImportanceRay> rays;
};

#endif /* end of include guard: __CAMERA_H__ */
