#include "TransparentSpecularMaterial.hpp"
#include "Formatting.hpp"


ImportanceRay TransparentSpecularMaterial::next(const ImportanceRay& incoming, const Vector3d& position, const Vector3d& normal, Sampler& sampler) {
  Vector3d direction;
  Vector3d new_position;
  Color importance = incoming.importance * reflected();
  if (sampler.random() > _opacity) {
      double angle = acos(incoming.direction().dot(normal));

      importance *= (1 -_opacity);
      direction = (incoming.direction() + fabs(sin(angle * 2.)) * normal).normalized();
      new_position = position + direction * 0.001;

      //assert(direction.dot(normal) <= 0.0);
  } else {
      importance *= _opacity;
      direction = Geometry::flip_vector_about(-incoming.direction(), normal);
      new_position = position + direction * 0.001;
  }
  return ImportanceRay(new_position, direction, importance);
}
