#ifndef __INTERSECTION_H__
#define __INTERSECTION_H__

#include <typeinfo>
#include <Eigen/Dense>
#include <limits>
#include "Formatting.hpp"
#include "Ray.hpp"
 

using namespace Eigen;
using namespace std;


class Surface;
class Intersection {
  friend ostream& operator<<(ostream& out, const Intersection& i);

public:
  Intersection(double distance, const Vector3d& location, const Surface& surface) : 
      _location(location), _surface(&surface), _distance(distance), _none(false) 
    {};

  static Intersection None() { return Intersection(true); };
  static Intersection Some() { return Intersection(false); };

  const Surface& surface() { return *_surface; };
  const Vector3d& location() { return _location; };
  double distance() { return _distance; };

  bool isNone() const { return _none; };
  bool isSome() const { return _distance == std::numeric_limits<double>::infinity(); };

  bool operator< (const Intersection& other) const {
      return _distance < other._distance;
  };

private:
  Intersection(bool result) : 
      _location(), _surface(NULL), _distance(std::numeric_limits<double>::infinity()), _none(result)
    {};

  Vector3d _location;
  const Surface* _surface;
  double _distance;
  bool _none;
};

ostream& operator<< (ostream& out, const Intersection& obj);

#include "Surface.hpp"

#endif /* end of include guard: __INTERSECTION_H__ */
