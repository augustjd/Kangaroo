#ifndef __SURFACE_H__
#define __SURFACE_H__

#include "Ray.hpp"

class Intersection;
class Surface {
public:
  Surface() {};
  virtual ~Surface () {};

  virtual Intersection intersect(const Ray& ray) const = 0;

  friend std::ostream& operator << (std::ostream& os, const Surface& b) {
      return b.print(os);
  }
protected:
    virtual std::ostream& print(std::ostream&) const = 0;
};

#include "Intersection.hpp"

#endif /* end of include guard: __SURFACE_H__ */
