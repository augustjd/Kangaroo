#ifndef __IMPORTANCE_RAY_H__
#define __IMPORTANCE_RAY_H__

#include "Ray.hpp"

class ImportanceRay : public Ray {
public:
    ImportanceRay(Vector3d origin, Vector3d direction, double _importance) : 
        Ray(origin, direction), importance(_importance) {};
    virtual ~ImportanceRay(){};

    const double importance;
};

std::ostream& operator<< (std::ostream& out, const ImportanceRay& obj);

#endif /* end of include guard: __IMPORTANCERAY_H__ */
