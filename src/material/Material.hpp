#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "geometry/ImportanceRay.hpp"

class Material {
public:
  Material() {};
  virtual ~Material () {};

  virtual ImportanceRay next(const Ray& incoming, const Vector3d& normal, const Sampler& sampler);
private:
  /* data */
};

#endif /* end of include guard: __MATERIAL_H__ */
