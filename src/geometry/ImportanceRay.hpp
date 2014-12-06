#ifndef __IMPORTANCE_RAY_H__
#define __IMPORTANCE_RAY_H__

#include "Ray.hpp"

class ImportanceRay : public Ray {
public:
    ImportanceRay(Vector3d origin, Vector3d direction, double importance) : 
        Ray(origin, direction), importance(_importance) {};
    virtual ~ImportanceRay(){};

    const double importance;
};


std::ostream& operator<< (std::ostream& out, const Ray& obj) {
  return out << BOLD_BLUE("ImportanceRay") "(" 
    << BOLD_GREEN("origin") "=" << obj.origin() << ", "
    << BOLD_GREEN("direction") "=" << obj.direction() << ", "
    << BOLD_GREEN("importance") "=" << obj.importance << ")";
}

#endif /* end of include guard: __IMPORTANCERAY_H__ */
