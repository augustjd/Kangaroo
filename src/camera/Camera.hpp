#ifndef __CAMERA_H__
#define __CAMERA_H__

class Camera {
public:
  Camera(const Vector2d& size, double focal_length) : 
    _size(size), _focal_length(focal_length), _output(NULL) {};

  Camera(const Vector2d& size, double focal_length, const sf::Image& output) : 
    _size(size), _focal_length(focal_length), _output(&output) {};

  virtual ~Camera(){};

private:
  Vector2d _size;
  double _focal_length;
  const sf::Image* _output;
};

#endif /* end of include guard: __CAMERA_H__ */
