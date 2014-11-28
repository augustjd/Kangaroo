#ifndef __INTERSECTION_H__
#define __INTERSECTION_H__

#include <typeinfo>
#include <Eigen/Dense>
#include "Formatting.hpp"

using namespace Eigen;
using namespace std;


class Surface;
class Intersection {
  friend ostream& operator<<(ostream& out, const Intersection& i);

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

ostream& operator<< (ostream& out, const Intersection& obj) {
  if (obj.isNone()) {
    return out << BOLD_BLUE("Intersection")"(none)";
  } else {
    return out << BOLD_BLUE("Intersection") << "("
      << BOLD_GREEN("location") << "=" << obj._location << ", "
      << BOLD_GREEN("surface") << "=" << typeid(*obj._surface).name() << ")";
  }
}

#include "Surface.hpp"

#endif /* end of include guard: __INTERSECTION_H__ */
