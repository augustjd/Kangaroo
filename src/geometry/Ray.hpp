#pragma once

#ifndef __RAY_H__
#define __RAY_H__

#include <Eigen/Dense>
#include "Formatting.hpp"

using namespace Eigen;

class Ray {
  friend ostream& operator<< (ostream&, const Ray&);
public:
  Ray (const Vector3d& direction) :
    _origin(Vector3d(0,0,0)),
    _direction(direction.normalized()),
    _inverse(Vector3d(1. / direction.x(), 1. / direction.y(), 1. / direction.z())),
    _inverse_component_sign{ (1. / direction.x()) > 0, (1. / direction.y()) > 0, (1. / direction.z()) > 0 }
    {};

  Ray (const Vector3d& origin, const Vector3d& direction) : 
    _origin(origin), 
    _direction(direction.normalized()),
    _inverse(Vector3d(1. / direction.x(), 1. / direction.y(), 1. / direction.z())),
    _inverse_component_sign{ (1. / direction.x()) > 0, (1. / direction.y()) > 0, (1. / direction.z()) > 0 }
    {};

  virtual ~Ray() {};

  const Vector3d& origin() const { return _origin; };
  const Vector3d& direction() const { return _direction; };
  const Vector3d& inverse() const { return _inverse; };

  Ray flipped() const { return Ray(_origin, -_direction); };
  Vector3d along(double distance) const { return _origin + (_direction * distance); };

  int inverse_x_sign() const { return _inverse_component_sign[0]; };
  int inverse_y_sign() const { return _inverse_component_sign[1]; };
  int inverse_z_sign() const { return _inverse_component_sign[2]; };

protected:
  Vector3d _origin;
  Vector3d _direction;
  Vector3d _inverse;
  int _inverse_component_sign[3];
};

std::ostream& operator<< (std::ostream& out, const Ray& obj);

#endif /* end of include guard: __RAY_H__ */
