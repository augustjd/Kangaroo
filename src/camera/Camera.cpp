#include "Camera.hpp"
 
Vector3d Camera::pixel_position(size_t x, size_t y) {
    return Vector3d(
            _width * ((double)x - width() / 2)/width(),
            _height * ((double)y - height() / 2)/height(),
            _focal_length
            );
};
