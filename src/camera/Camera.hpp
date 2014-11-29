#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <SFML/Graphics.hpp>
#include "Formatting.hpp"

using namespace std;

class Camera {
public:
  Camera(const Vector2d& size, double focal_length, sf::Image& output) : 
    _size(size), _focal_length(focal_length), _output(output),
    sample_count(output.getSize().y) {
      _texture.loadFromImage(output);
      reset_image();
      _sprite.setTexture(_texture, true);
    };

  virtual ~Camera(){};

  size_t width()  { return _output.getSize().x; }
  size_t height() { return _output.getSize().y; }
  size_t pixel_count() { return width() * height() ; }

  Vector3d pixel_position(size_t x, size_t y) {
      return Vector3d(
              -width() / 2  + (x + 0.5)_size.x() / width(),
              -height() / 2 + (y + 0.5)_size.y() / height(),
              focal_length
              );
  }

  const sf::Color operator() (size_t x, size_t y) { 
    return _output.getPixel(x, y); 
  };

  sf::Color color_after_sample(size_t x, size_t y, const sf::Color& color) {
    Vector3d current = from_color((*this)(x,y));
    Vector3d sample  = from_color(color);

    size_t samples = sample_count[y][x];

    return to_color((current * samples + sample) / (samples + 1));
  }

  size_t next = 0;
  void make_sample() {
    if (next < pixel_count()) {
      size_t x = next % width();
      size_t y = next / width();

      update_with_sample(x, y, sf::Color::Black);

      next += 1;
    }
  }

  const sf::Sprite& sprite() { return _sprite; };

private:
  void reset_image() {
      for (size_t i = 0; i < height(); i++) {
        auto& row = sample_count[i];
        row = vector<size_t>(width());
        row.resize(width());
        std::fill(row.begin(), row.end(), 0);
      }
  }

  Vector3d from_color(const sf::Color& v) {
    return Vector3d(
        (double)v.r / 255.0,
        (double)v.g / 255.0,
        (double)v.b / 255.0
        );
  }
  sf::Color to_color(const Vector3d& v) {
    return sf::Color(
        (sf::Uint8)v.x() * 255.0,
        (sf::Uint8)v.y() * 255.0,
        (sf::Uint8)v.z() * 255.0
        );
  }

  sf::Color& update_with_sample(size_t x, size_t y, const sf::Color& color) {
#ifdef PRINT_SAMPLES
    cout << "Sampled (" << x << ", " << y << ") for color " << color << endl;
#endif
    sf::Color new_color = color_after_sample(x, y, color);

    _output.setPixel(x, y, new_color);
    sample_count[y][x] += 1;
    _texture.update(_output);
  };

  vector<vector<size_t>> sample_count;

  Vector2d _size;
  double _focal_length;
  sf::Image& _output;
  sf::Texture _texture;
  sf::Sprite _sprite;
};

#endif /* end of include guard: __CAMERA_H__ */
