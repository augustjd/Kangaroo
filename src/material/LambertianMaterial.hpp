#ifndef __LAMBERTIANMATERIAL_H__
#define __LAMBERTIANMATERIAL_H__

#include "sampling/Sampler.hpp"
#include "Constants.hpp"
#include "Material.hpp"

static const double DISTANCE_AWAY_FROM_SURFACE = 0.1;
class LambertianMaterial : public Material {
public:
  LambertianMaterial(Color color, Color emit) : _color(color), _emit(emit) {};
  LambertianMaterial() : _color(0.5), _emit(0.0) {};
  virtual ~LambertianMaterial() {};

  virtual ImportanceRay next(const ImportanceRay& incoming, const Vector3d& position, const Vector3d& normal, Sampler& sampler) {
      Vector3d direction = sampler.random_direction_in_hemisphere(normal);
      return ImportanceRay(position, direction, incoming.importance * 1.0 / PI);
  }
  virtual Color color() const {
      return _color;
  }
  virtual Color emission() const {
      return _emit;
  }
  virtual bool is_emitter() const { return _emit.luminance() > 0; };

  virtual std::ostream& print(std::ostream& os) const {
      return os << BOLD_BLUE("LambertianMaterial") "(" 
          << BOLD_GREEN("color")"=" << color()
          << BOLD_GREEN("emission")"=" << emission()
          << ")";
  }
private:
  Color _color;
  Color _emit;
};  

#endif /* end of include guard: __LAMBERTIANMATERIAL_H__ */    
