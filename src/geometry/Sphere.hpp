#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "Surface.hpp"

using namespace std;

class Sphere : public Surface {
public:
  Sphere(Vector3d center, double radius) : _center(center), _radius(radius) {};
  virtual ~Sphere () {};

  virtual Intersection intersect(const Ray& ray) const {
    // see http://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
    Vector3d difference = ray.origin() - center();
    double b = ray.direction().dot(ray.origin() - center());
    double r = radius();
    double criterion = b*b - difference.dot(difference) + r*r;

    if (criterion < 0.0) {
      return Intersection::None();
    } else {
      double d1 = -b + sqrt(criterion);
      double d2 = -b - sqrt(criterion);

      double first_intersection_distance = min(d1, d2);

      return Intersection(ray.along(first_intersection_distance), *this);
    }
  };


  const Vector3d& center() const { return _center; };
  const double radius() const { return _radius; };
private:
  Vector3d _center;
  double _radius;
};

std::ostream& operator<< (std::ostream& out, Sphere obj) {
  return out << "Sphere(r=" << obj.radius() << ", center=(" << obj.center().transpose() << "))";
}

#endif /* end of include guard: __SPHERE_H__ */
