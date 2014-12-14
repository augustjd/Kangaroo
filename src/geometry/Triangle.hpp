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
    const Vector3d& n = _normal;

    double distance = n.dot(_a - ray.origin()) / n.dot(ray.direction());
    if (distance < 0.0) {
      return Intersection::None();
    }

    Vector3d plane_intersection = ray.along(distance);
    Vector3d w = plane_intersection - _a;
    double uv = _ab.dot(_ac); 

    double wv = w.dot(_ac);
    double wu = w.dot(_ab);

    double uu = _ab.dot(_ab);
    double vv = _ac.dot(_ac);
    double denom = 1 / ((uv*uv) - (uu*vv));

    double s = ((uv*wv) - (vv*wu)) * denom;
    double t = ((uv*wu) - (uu*wv)) * denom;

    if (s < 0.0 || t < 0.0 || s + t > 1.0) {
      return Intersection::None();
    }

    return Intersection(distance, plane_intersection, *this);
  };

  const Vector3d& ab() const { return _ab; };
  const Vector3d& bc() const { return _bc; };
  const Vector3d& ac() const { return _ac; };

  const Vector3d& normal() const { return _normal; };

  double area() const { return _area; };

protected:
  virtual std::ostream& print(std::ostream& out) const {
  return out << BOLD_BLUE("Triangle") "("
    << BOLD_GREEN("a") "=" << vector_to_str(_a) << ", "
    << BOLD_GREEN("b") "=" << vector_to_str(_b) << ", "
    << BOLD_GREEN("c") "=" << vector_to_str(_c) << ")";
  }

private:
  Vector3d _a, _b, _c, _ab, _bc, _ac, _normal;
  double _area;
};

#endif /* end of include guard: __TRIANGLE_H__ */
