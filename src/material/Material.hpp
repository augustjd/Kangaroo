#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "geometry/ImportanceRay.hpp"
#include "sampling/Sampler.hpp"
#include "Formatting.hpp"
 

class Material {
public:
  Material() {};
  virtual ~Material () {};

  virtual ImportanceRay next(const Ray& incoming, const Vector3d& normal, const Sampler& sampler) = 0;
  virtual bool is_emitter() = 0;

  friend std::ostream& operator << (std::ostream& os, const Material& b) {
      return b.print(os);
  }
protected:
    virtual std::ostream& print(std::ostream&) const = 0;
};

#endif /* end of include guard: __MATERIAL_H__ */
