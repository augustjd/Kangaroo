#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <Eigen/Dense>
#include <Eigen/Geometry>

using namespace Eigen;

class Geometry {

public:
    static Matrix3d align_vectors_matrix(const Vector3d& a, const Vector3d& b) {
        double theta = acos(a.dot(b));
        Vector3d axis = a.cross(b).normalized();

        Matrix3d rotation;
        rotation = AngleAxisd(theta, axis);
        return rotation;
        /*
        Vector3d v = a.cross(b).normalized();

        Matrix3d skew;
        skew << 0, -v[2], v[1],
                v[2], 0, -v[0],
                -v[1], v[0], 0;

        double c = a.dot(b);
        double s = v.norm();

        return Matrix3d::Identity() + skew + (skew * skew * (1 - c / (s*s)));
        */
    }
    static Vector3d flip_vector_about(Vector3d x, Vector3d about) {
        Matrix3d align = align_vectors_matrix(x, about);
        return align * align * x;
    }

    const static Vector3d x_unit;
    const static Vector3d y_unit;
    const static Vector3d z_unit;
};

#endif /* end of include guard: __GEOMETRY_H__ */
