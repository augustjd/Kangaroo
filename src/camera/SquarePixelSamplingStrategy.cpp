#include "SquarePixelSamplingStrategy.hpp"

Pixel SquarePixelSamplingStrategy::next() {
    if (_square_row == _squares_down) {
        return Pixel::Invalid(); 
    }

    assert(_square_column < _squares_across);

    size_t square_width;
    size_t square_height;

    load_current_square_size(square_width, square_height);

    // offsets within current square
    size_t x_offset = _square_index % square_width;
    size_t y_offset = _square_index / square_width;

    size_t x = (_square_column * _square_size) + x_offset;
    size_t y = (_square_row * _square_size)    + y_offset;

    _square_index += 1;

    if (_square_index == square_width * square_height) {
        _square_index = 0;

        if (_square_column < _squares_across - 1) {
            // move right
            _square_column += 1;
        } else {
            // move down
            _square_column = 0;
            _square_row += 1;
        }
    }

    return Pixel(x,y);
}

void SquarePixelSamplingStrategy::load_current_square_size(size_t& width, size_t& height) {
    // last_column
    if (_square_column < _squares_across - 1) {
        width = _square_size;
    } else {
        width = (_x - (_square_column * _square_size));
    }

    if (_square_row < _squares_down- 1) {
        height = _square_size;
    } else {
        height = (_y - (_square_row * _square_size));
    }
}

void SquarePixelSamplingStrategy::reset() { 
    _square_row = 0;
    _square_column = 0;
    _square_index = 0;
};
