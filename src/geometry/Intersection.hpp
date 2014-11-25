#ifndef __INTERSECTION_H__
#define __INTERSECTION_H__

#include <Eigen/Dense>

using namespace Eigen;

class Surface;
class Intersection {
public:
  Intersection(const Vector3d& location, const Surface& surface) : _location(location), _surface(&surface), _none(false) {};

  static Intersection None() { return Intersection(); };

  const Surface& surface() { return *_surface; };
  const Vector3d& location() { return _location; };

  bool isNone() const { return _none; };
private:
  Intersection() : _surface(NULL), _location(), _none(true) {};

  const Vector3d _location;
  const Surface* _surface;
  const bool _none;
};

#include "Surface.hpp"

#endif /* end of include guard: __INTERSECTION_H__ */
