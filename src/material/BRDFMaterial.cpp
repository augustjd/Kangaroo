#include "BRDFMaterial.hpp"
#include "geometry/Geometry.hpp"

ImportanceRay BRDFMaterial::next(const ImportanceRay& incoming, 
                                 const Vector3d& position, 
                                 const Vector3d& normal, 
                                 Sampler& sampler) {
    Vector3d opposite = -incoming.direction();

    double theta_in = acos(normal.dot(opposite));
    double phi_in   = acos(opposite.dot(Geometry::z_unit));

    AngleSample sample = _brdf->sample(theta_in, sampler);
    Matrix3d local_to_world = Geometry::align_vectors_matrix(Geometry::y_unit, normal);
    Vector3d local_direction(cos(phi_in + sample.phi),
                             cos(sample.theta),
                             sin(phi_in + sample.phi));
    Vector3d result = local_to_world * local_direction;

    return ImportanceRay(position, result, sample.importance * incoming.importance);
}
