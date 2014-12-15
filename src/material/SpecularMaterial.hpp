#pragma once

#include "sampling/Sampler.hpp"
#include "Constants.hpp"
#include "Material.hpp"
#include "geometry/Geometry.hpp"
 
class SpecularMaterial : public Material {
public:
  SpecularMaterial(Color color, Color emit) : _color(color), _emit(emit) {};
  SpecularMaterial() : _color(0.5), _emit(0.0) {};
  virtual ~SpecularMaterial() {};

  virtual ImportanceRay next(const ImportanceRay& incoming, const Vector3d& position, const Vector3d& normal, Sampler& sampler) {
      Vector3d direction = Geometry::flip_vector_about(-incoming.direction(), normal);
      assert(direction.dot(normal) > 0.0);
      Color importance = incoming.importance * color();
      return ImportanceRay(position, direction, importance);
  }
  virtual Color color() const {
      return _color;
  }
  virtual Color emission() const {
      return _emit;
  }
  virtual bool is_emitter() const { return _emit.luminance() > 0; };

  virtual std::ostream& print(std::ostream& os) const {
      return os << BOLD_BLUE("SpecularMaterial") "(" 
          << BOLD_GREEN("color")"=" << color()
          << BOLD_GREEN("emission")"=" << emission()
          << ")";
  }
private:
  Color _color;
  Color _emit;
};  
