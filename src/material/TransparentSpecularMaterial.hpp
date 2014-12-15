#pragma once

#include "sampling/Sampler.hpp"
#include "Constants.hpp"
#include "Material.hpp"
#include "geometry/Geometry.hpp"
 
class TransparentSpecularMaterial : public Material {
public:
  TransparentSpecularMaterial(Color color, Color emit, double opacity) : _color(color), _emit(emit), _opacity(opacity) {};
  TransparentSpecularMaterial(Color color, Color emit) : _color(color), _emit(emit), _opacity(1.0) {};
  TransparentSpecularMaterial() : _color(0.5), _emit(0.0), _opacity(1.0) {};
  virtual ~TransparentSpecularMaterial() {};

  virtual ImportanceRay next(const ImportanceRay& incoming, const Vector3d& position, const Vector3d& normal, Sampler& sampler) {
      Vector3d direction;
      Vector3d new_position;
      Color importance = incoming.importance * color();
      if (sampler.random() > _opacity) {
          double angle = acos(incoming.direction().dot(normal));

          importance *= (1 -_opacity);
          direction = (incoming.direction() + fabs(sin(angle * 2.)) * normal).normalized();
          new_position = position + direction * 0.001;

          //assert(direction.dot(normal) <= 0.0);
      } else {
          importance *= _opacity;
          direction = Geometry::flip_vector_about(-incoming.direction(), normal);
          new_position = position;
      }
      return ImportanceRay(new_position, direction, importance);
  }
  virtual Color color() const {
      return _color;
  }
  virtual Color emission() const {
      return _emit;
  }
  virtual bool is_emitter() const { return _emit.luminance() > 0; };

  virtual std::ostream& print(std::ostream& os) const {
      return os << BOLD_BLUE("TransparentSpecularMaterial") "(" 
          << BOLD_GREEN("color")"=" << color()
          << BOLD_GREEN("emission")"=" << emission()
          << ")";
  }
private:
  Color _color;
  Color _emit;
  double _opacity;
};  
