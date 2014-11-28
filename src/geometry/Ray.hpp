#ifndef __RAY_H__
#define __RAY_H__

#include <Eigen/Dense>
#include "Formatting.hpp"

using namespace Eigen;

class Ray {
  friend ostream& operator<< (ostream&, const Ray&);
public:
  Ray (const Vector3d& direction_) :
    _origin(Vector3d(0,0,0)),
    _direction(direction_.normalized()) {};

  Ray (const Vector3d& origin_, const Vector3d& direction_) : 
    _origin(origin_), 
    _direction(direction_.normalized()) {};

  virtual ~Ray() {};

  const Vector3d& origin() const { return _origin; };
  const Vector3d& direction() const { return _direction; };

  Ray flipped() const { return Ray(_origin, -_direction); };
  Vector3d along(double distance) const { return _origin + (_direction * distance); };
private:
  Vector3d _origin;
  Vector3d _direction;
};

std::ostream& operator<< (std::ostream& out, const Ray& obj) {
  return out << BOLD_BLUE("Ray") "(" 
    << BOLD_GREEN("origin") "=" << obj.origin() << ", "
    << BOLD_GREEN("direction") "=" << obj.direction() << ")";
}


#endif /* end of include guard: __RAY_H__ */
