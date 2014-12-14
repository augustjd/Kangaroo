#ifndef __LAMBERTIANMATERIAL_H__
#define __LAMBERTIANMATERIAL_H__

#include "Material.hpp"

class LambertianMaterial : public Material {
public:
    LambertianMaterial() {};
    virtual ~LambertianMaterial(){};

  virtual ImportanceRay next(const Ray& incoming, const Vector3d& normal, const Sampler& sampler) {};
  virtual bool is_emitter() { return false; };

  virtual std::ostream& print(std::ostream& os) const {
      return os << BOLD_BLUE("LambertianMaterial") "(" << ")";
  }
private:
    
};  

#endif /* end of include guard: __LAMBERTIANMATERIAL_H__ */    
