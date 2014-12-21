#ifndef __LAMBERTIANMATERIAL_H__
#define __LAMBERTIANMATERIAL_H__

#include "sampling/Sampler.hpp"
#include "Constants.hpp"
#include "Material.hpp"

static const double DISTANCE_AWAY_FROM_SURFACE = 0.1;
class LambertianMaterial : public ConstantColorMaterial {
public:
  LambertianMaterial(const Color& reflected, const Color& emitted) : ConstantColorMaterial(reflected, emitted) {};
  LambertianMaterial() : ConstantColorMaterial(Color(0.5), Color(0.0)) {};
  virtual ~LambertianMaterial() {};

  virtual ImportanceRay next(const ImportanceRay& incoming, const Vector3d& position, const Vector3d& normal, Sampler& sampler) {
      Vector3d direction = sampler.random_direction_in_hemisphere(normal);
      return ImportanceRay(position + direction * 0.01, direction, incoming.importance * 1.0 / Constants::PI);
  }

  virtual std::ostream& print(std::ostream& os) const {
      return os << BOLD_BLUE("LambertianMaterial") "(" 
          << BOLD_GREEN("reflected")"=" << reflected()
          << BOLD_GREEN("emitted")"=" << emitted()
          << ")";
  }
};  

#endif /* end of include guard: __LAMBERTIANMATERIAL_H__ */    
