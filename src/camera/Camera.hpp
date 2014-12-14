#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <cstdlib>
#include <Eigen/Dense>

using namespace Eigen;

class Camera {
public:
    Camera(size_t width, size_t height, double focal_length) :
        _width(width), _height(height), _focal_length(focal_length)
    {};

    virtual ~Camera(){};

    size_t width() { return _width; };
    size_t height() { return _height; };

    Vector3d position_of_pixel(size_t x, size_t y);

private:
    size_t _width;
    size_t _height;

    double _focal_length;
};

#endif /* end of include guard: __CAMERA_H__ */
