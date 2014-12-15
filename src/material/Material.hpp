#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "geometry/ImportanceRay.hpp"
#include "sampling/Sampler.hpp"
#include "color/Color.hpp"
 
#include "Formatting.hpp"
 

class Material {
public:
  Material() {};
  virtual ~Material () {};

  virtual ImportanceRay next(const ImportanceRay& incoming, const Vector3d& position, const Vector3d& normal, Sampler& sampler) = 0;
  virtual bool is_emitter() const = 0;
  virtual Color emission() const = 0;

  friend std::ostream& operator << (std::ostream& os, const Material& b) {
      return b.print(os);
  }
protected:
  virtual std::ostream& print(std::ostream&) const = 0;
};

#endif /* end of include guard: __MATERIAL_H__ */
