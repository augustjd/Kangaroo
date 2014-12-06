#ifndef __SQUAREPIXELSQAMPLINGSTRATEGY_H__
#define __SQUAREPIXELSQAMPLINGSTRATEGY_H__

#include "PixelSamplingStrategy.hpp"

// rather than usual int division flooring, take ceil. This way, you
// can guarantee complete coverage of the grid, as below.
#define CEIL_DIV(num, denom) num % denom == 0 ? num / denom : num / denom + 1

class SquarePixelSamplingStrategy : public PixelSamplingStrategy {
public:
    SquarePixelSamplingStrategy(size_t x, size_t y, size_t square_size = 50) : 
        PixelSamplingStrategy(x,y), 
        _square_size(square_size), 
        _square_row(0),
        _square_column(0),
        _square_index(0),
       _squares_across(CEIL_DIV(x, square_size)),
       _squares_down(CEIL_DIV(y, square_size)) 
    {};

    virtual ~SquarePixelSamplingStrategy(){};

    virtual Pixel next();
    virtual void reset(); 

private:

    void load_current_square_size(size_t& width, size_t& height);
    size_t _square_size;


    size_t _square_row;
    size_t _square_column;

    size_t _square_index;

    size_t _squares_across;
    size_t _squares_down;

};

#endif /* end of include guard: __SQUAREPIXELSQAMPLINGSTRATEGY_H__ */
