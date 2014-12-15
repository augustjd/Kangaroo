#ifndef __COLOR_H__
#define __COLOR_H__

#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <algorithm>


#include "Formatting.hpp"

using namespace Eigen;

class Color : public Vector3d {
public:
    Color() {};
    Color(double r, double g, double b) : Vector3d(r, g, b) {};
    Color(double val) : Vector3d(val, val, val) {};
    Color(Vector3d v) : Vector3d(v) {};
    Color(const Color& other) : Vector3d(other.x(), other.y(), other.z()) {};

    sf::Color as_sfml_color() const {
        return sf::Color(
                std::min(255.0, 255 * x()),
                std::min(255.0, 255 * y()),
                std::min(255.0, 255 * z())
                );
    }

    Color& operator= (const Vector3d& rhs) {
        (*this).x() = rhs.x();
        (*this).y() = rhs.y();
        (*this).z() = rhs.z();

        return *this;
    }

    Color operator* (const Color& rhs) const {
        return Color(x() * rhs.x(),
                     y() * rhs.y(),
                     z() * rhs.z());
    }


    Color& operator*= (const double rhs) {
        x() *= rhs;
        y() *= rhs;
        z() *= rhs;

        return *this;
    }

    double luminance() const {
        return 0.2126 * x() + 0.7152 * y() + 0.0722 * z();
    }
};

ostream& operator<<(ostream& out, const Color& color);


#endif /* end of include guard: __COLOR_H__ */
