#include "Camera.hpp"

Vector3d Camera::position_of_pixel(size_t x, size_t y) {
    return Vector3d(
            (x - (_width / 2.0)),
            (y - (_height / 2.0)),
            _focal_length
            );
}
