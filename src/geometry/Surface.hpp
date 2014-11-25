#ifndef __SURFACE_H__
#define __SURFACE_H__

#include "Ray.hpp"

class Intersection;
class Surface {
public:
  Surface() {};
  virtual ~Surface () {};

  virtual Intersection intersect(const Ray& ray) const = 0;

private:
};

#include "Intersection.hpp"

#endif /* end of include guard: __SURFACE_H__ */
