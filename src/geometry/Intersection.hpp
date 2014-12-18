#ifndef __INTERSECTION_H__
#define __INTERSECTION_H__

#include <typeinfo>
#include <Eigen/Dense>
#include <limits>

#include "Formatting.hpp"
#include "geometry/Ray.hpp"

using namespace Eigen;

class SceneObject;
class Intersection {
  friend std::ostream& operator<<(std::ostream& out, const Intersection& i);

public:
  Intersection(double distance, const Vector3d& location, const Vector3d& normal) : 
      _location(location), _normal(normal), _object(NULL), _distance(distance), _none(false) 
    {};

  Intersection(double distance, const Vector3d& location, const Vector3d& normal, SceneObject& object) : 
      _location(location), _normal(normal), _object(&object), _distance(distance), _none(false) 
    {};

  static Intersection None() { return Intersection(true); };
  static Intersection Some() { return Intersection(false); };

  bool has_object() { return _object != NULL; };
  const SceneObject& object() const { return *_object; };
  Intersection& set_object(SceneObject& obj) { _object = &obj; return *this; };
  const Vector3d& location() const { return _location; };
  const Vector3d& normal() const { return _normal; };
  double distance() { return _distance; };

  bool isNone() const { return _none; };
  bool isSome() const { return _distance == std::numeric_limits<double>::infinity(); };

  bool operator< (const Intersection& other) const {
      return _distance < other._distance;
  };

private:
  Intersection(bool result) : 
      _location(), _object(NULL), _distance(std::numeric_limits<double>::infinity()), _none(result)
    {};

  Vector3d _location;
  Vector3d _normal;
  SceneObject* _object;
  double _distance;
  bool _none;
};

#include "scene/SceneObject.hpp"

#endif /* end of include guard: __INTERSECTION_H__ */
