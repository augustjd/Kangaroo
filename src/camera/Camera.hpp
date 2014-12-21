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
#include "xml/XmlUtilities.hpp"

#include "xml/tinyxml2.hpp"

using namespace Eigen;
using std::vector;
using namespace tinyxml2;

static Sampler sampler;
class Camera {
    static constexpr size_t default_passes = 20;
public:
    Camera(shared_ptr<sf::Image>& image, double fovx, const Scene& scene) :
        _image(image), 
        _width(image->getSize().x), 
        _passes(default_passes),
        _up(0,1,0),
        _direction(0,0,1),
        _height(image->getSize().y), 
        _focal_length(fabs((image->getSize().x / 2.0)/tan(Constants::degrees_to_radians(fovx/2.0)))), 
        _scene(scene),
        _done(false),
        _reset(false),
        _tracer(new DepthPathTracer(sampler, 4))
    {
        _position = Vector3d(0, 0, -_focal_length);
        _right = _direction.cross(_up).normalized();
        initialize_samples();
    };

    Camera(size_t passes, Vector3d position, Vector3d up, shared_ptr<sf::Image>& image, double fovx, const Scene& scene) :
        _image(image), 
        _width(image->getSize().x), 
        _passes(passes),
        _position(position),
        _direction(0,0,1),
        _up(up.normalized()),
        _height(image->getSize().y), 
        _focal_length(fabs((image->getSize().x / 2.0)/tan(Constants::degrees_to_radians(fovx/2.0)))), 
        _scene(scene),
        _done(false),
        _reset(false),
        _tracer(new DepthPathTracer(sampler, 4))
    {
        _right = _direction.cross(_up).normalized();
        initialize_samples();
    };

    virtual ~Camera() {};

    shared_ptr<sf::Image> image() const { return shared_ptr<sf::Image>(_image); };

    size_t width() { return _width; };
    size_t height() { return _height; };
    size_t pixels() { return _width * _height; };

    void move(Vector3d offset) {
        set_position(_position + offset);
    }

    void move_right(double distance) {
        set_position(_position + _right * distance);
    }

    void move_up(double distance) {
        set_position(_position + _up * distance);
    }

    void move_in(double distance) {
        set_position(_position + _direction * distance);
    }

    void set_position(Vector3d position) {
        _position = position;
        _right = _direction.cross(_up).normalized();
        _reset = true;

        cout << "New camera position:" << vector_to_str(position) << endl;
    }

    void set_up(Vector3d up) {
        _up = up.normalized();
        _right = _direction.cross(_up).normalized();
        _reset = true;
    }

    void set_position_and_up(Vector3d position, Vector3d up) {
        _position = position;
        _up = up.normalized();
        _right = _direction.cross(_up).normalized();
        _reset = true;
    }

    void set_position_direction_and_up(Vector3d position, Vector3d direction, Vector3d up) {
        _position = position;
        _direction = direction.normalized();
        _up = up.normalized();
        _right = _direction.cross(_up).normalized();
        _reset = true;
    }

    void set_look_at(Vector3d position, Vector3d at) {
        set_position_direction_and_up(position, at - position, _up);
    }

    Vector3d position_of_pixel(size_t x, size_t y) {
        double x_rel = ((double)x - (double)(_width / 2.0));
        double y_rel = ((double)y - (double)(_height / 2.0));

        return _position + (_right * x_rel) + (_up * y_rel) + (_direction * _focal_length);
    }

    void sample() {
        std::chrono::high_resolution_clock::time_point t1, t2;
        for (size_t i = 0; i < _passes; i++) {
            t1 = std::chrono::high_resolution_clock::now();
            for(Sample& s : samples) {
                s += _tracer->trace(_scene, s.ray);
                _image->setPixel(s.x, s.y, s.as_sfml_color());
            }
            t2 = std::chrono::high_resolution_clock::now();

            if (_reset) {
                i = 0;
                _reset = false;
                cout << "Resetting pass." << endl;
                refresh_samples();
            } else {
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
                cout << "Finished pass " << BOLD_BLUE(i+1) << "/" << _passes << " in " << BOLD_GREEN(duration << "ms.") << endl;
            }
        }
        _done = true;
    }

    bool done() const { return _done; };

    static unique_ptr<Camera> load_from_xml(const XMLElement* el, const Scene* scene);

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

            rays.emplace_back(_position, (position_of_pixel(x, y) - _position).normalized(), 1.0);
            samples.emplace_back(x, y, rays[i]);
        }
    }

    void refresh_samples() {
        for (size_t i = 0; i < pixels(); i++) {
            size_t x = i % _width;
            size_t y = i / _width;

            rays[i] = ImportanceRay(_position, (position_of_pixel(x, y) - _position).normalized(), 1.0);
            samples[i].reset();
        }
    }

    bool _done;
    bool _reset;

    Vector3d _position;
    Vector3d _direction;
    Vector3d _up;
    Vector3d _right;

    shared_ptr<sf::Image> _image;
    const Scene& _scene;

    size_t _width;
    size_t _height;

    double _focal_length;

    size_t _passes;

    unique_ptr<Tracer> _tracer;

    vector<Sample> samples;
    vector<ImportanceRay> rays;
};

#endif /* end of include guard: __CAMERA_H__ */
