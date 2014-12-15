#ifndef __SAMPLE_H__
#define __SAMPLE_H__

#include "Color.hpp"
#include "geometry/ImportanceRay.hpp"
 
class Sample {
public:
    Sample(size_t _x, size_t _y, ImportanceRay& _ray) 
        : x(_x), y(_y), _n(0), _color(), ray(_ray) {};

    Sample(size_t _x, size_t _y, const Color& color, ImportanceRay& _ray) 
    : x(_x), y(_y), _n(1), _color(color), ray(_ray) {};

    virtual ~Sample(){};

    Sample& operator+=(const Color& rhs) {
        _color = (_color * _n + rhs) / (_n + 1);
        _n += 1;

        return *this;
    }

    ImportanceRay& ray;

    sf::Color as_sfml_color() {
        return _color.as_sfml_color();
    }

    sf::Color update(const Color& color) {
        (*this) += color;
        return as_sfml_color();
    }

    size_t x;
    size_t y;
private:

    size_t _n;

    Color _color;
};

#endif /* end of include guard: __SAMPLE_H__ */
