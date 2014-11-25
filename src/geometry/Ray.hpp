#ifndef __RAY_H__
#define __RAY_H__

#include <Eigen/Dense>

using namespace Eigen;

class Ray {
public:
  Ray (const Vector3d& direction_) :
    _start(Vector3d(0,0,0)),
    _direction(direction_.normalized()) {};

  Ray (const Vector3d& start_, const Vector3d& direction_) : 
    _start(start_), 
    _direction(direction_.normalized()) {};

  virtual ~Ray() {};

  const Vector3d& start() { return _start; };
  const Vector3d& direction() { return _direction; };
private:
  Vector3d _start;
  Vector3d _direction;
};

std::ostream& operator<< (std::ostream& out, Ray obj) {
  return out << "Ray((" << obj.start().transpose() << ") -> <" << obj.direction().transpose() << ">)";
}


#endif /* end of include guard: __RAY_H__ */
