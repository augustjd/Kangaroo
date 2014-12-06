#ifndef __PIXELSAMPLINGSTRATEGY_H__
#define __PIXELSAMPLINGSTRATEGY_H__

#include <iostream>
#include <cassert>

class Pixel {
public:
    Pixel(size_t _x, size_t _y) : x(_x), y(_y), valid(true) {};

    const size_t x, y;
    const bool valid;

    static Pixel Invalid() { return Pixel(); };

    operator bool() const { return valid; };

    bool operator== (const Pixel& r) { return x == r.x && y == r.y; };
private:
    Pixel() : x(0), y(0), valid(false) {};
};

class PixelSamplingStrategy {
public:
    PixelSamplingStrategy(size_t x, size_t y) : _x(x), _y(y) {};
    virtual ~PixelSamplingStrategy(){};

    virtual Pixel next() = 0;
    virtual void reset() = 0;

protected:
    size_t _x, _y;
    
};

#endif /* end of include guard: __PIXELSAMPLINGSTRATEGY_H__ */
