#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "Surface.hpp"
#include "Formatting.hpp"

using namespace std;

class Triangle : public Surface {
  friend ostream& operator<<(ostream& out, const Triangle& tri);
public:
  Triangle(const Vector3d& a, const Vector3d& b, const Vector3d& c) : 
    _a(a), _b(b), _c(c),
    _ab(_b - _a), _bc(_c - _b), _ac(_c - _a),
    _area(fabs((_b - _a).cross(_c - _a).norm() / 2.0)),
    _normal((_b - _a).cross(_b - _c).normalized()) {};

  virtual ~Triangle() {};

  virtual Intersection intersect(const Ray& ray) const {
    const Vector3d& n = normal();

    double distance = n.dot(_a - ray.origin()) / n.dot(ray.direction());
    if (distance < 0.0) {
      return Intersection::None();
    }

    Vector3d plane_intersection = ray.along(distance);
    Vector3d plane_intersection_offset = plane_intersection - _a;
    double u = plane_intersection_offset.dot(_ab);
    double v = (plane_intersection_offset - _ab * u).dot(_ac);

    if (u < 0.0 || v < 0.0 || u + v > 1.0) {
      return Intersection::None();
    }

    return Intersection(plane_intersection, *this);
  };

  const Vector3d& ab() const { return _ab; };
  const Vector3d& bc() const { return _bc; };
  const Vector3d& ac() const { return _ac; };

  const Vector3d& normal() const { return _normal; };

  double area() const { return _area; };

private:
  Vector3d _a, _b, _c, _ab, _bc, _ac, _normal;
  double _area;
};

std::ostream& operator<< (std::ostream& out, const Triangle& obj) {
  return out << BOLD_BLUE("Triangle") "("
    << BOLD_GREEN("a") "=" << obj._a << ", "
    << BOLD_GREEN("b") "=" << obj._b << ", "
    << BOLD_GREEN("c") "=" << obj._c << ")";
}

#endif /* end of include guard: __TRIANGLE_H__ */
