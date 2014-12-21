#include "BRDFMaterial.hpp"
#include "geometry/Geometry.hpp"
#include "Constants.hpp"

ImportanceRay BRDFMaterial::next(const ImportanceRay& incoming, 
                                 const Vector3d& position, 
                                 const Vector3d& normal, 
                                 Sampler& sampler) {
    Vector3d opposite = -incoming.direction();

    Vector3d u = normal.cross(Geometry::z_unit);
    Vector3d v = u.cross(normal);

    // eliminate the normal component in opposite.
    Vector3d surface_projection = (opposite - normal * opposite.dot(normal)).normalized();

    double theta_in = acos(normal.dot(opposite));
    double phi_in   = max(acos(surface_projection.dot(u)), acos(surface_projection.dot(v)) + Constants::PI_OVER_TWO);

    AngleSample sample = _brdf->sample(theta_in, sampler);
    Matrix3d local_to_world = Geometry::align_vectors_matrix(Geometry::x_unit, u) * Geometry::align_vectors_matrix(Geometry::y_unit, normal);
    Vector3d local_direction(cos(phi_in + sample.phi),
                             cos(sample.theta),
                             sin(phi_in + sample.phi));
    //Vector3d result = local_to_world * local_direction;
    Matrix3d rot = Geometry::align_vectors_matrix(opposite, normal);
    Vector3d result = rot * rot * opposite; // specular direction

    return ImportanceRay(position + result * 0.001, result, sample.importance * incoming.importance);
}
