#pragma once

#include "sampling/Sampler.hpp"
#include "Constants.hpp"
#include "Material.hpp"
#include "geometry/Geometry.hpp"
 
class TransparentSpecularMaterial : public ConstantColorMaterial {
public:
  TransparentSpecularMaterial(Color reflected, Color emitted, double opacity) : ConstantColorMaterial(reflected, emitted), _opacity(opacity) {};
  TransparentSpecularMaterial(Color reflected, Color emitted) : ConstantColorMaterial(reflected, emitted), _opacity(1.0) {};
  TransparentSpecularMaterial() : ConstantColorMaterial(Color(0.5), Color(0.0)), _opacity(1.0) {};

  virtual ~TransparentSpecularMaterial() {};

  virtual ImportanceRay next(const ImportanceRay& incoming, const Vector3d& position, const Vector3d& normal, Sampler& sampler);

  virtual std::ostream& print(std::ostream& os) const {
      return os << BOLD_BLUE("TransparentSpecularMaterial") "(" 
          << BOLD_GREEN("reflected")"=" << reflected()
          << BOLD_GREEN("emitted")"=" << emitted()
          << ")";
  }
private:
  Color _color;
  Color _emit;
  double _opacity;
};  
