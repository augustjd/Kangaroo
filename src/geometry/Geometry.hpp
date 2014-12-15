#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <Eigen/Dense>

using namespace Eigen;

class Geometry {

public:
    static Matrix3d align_vectors_matrix(Vector3d a, Vector3d b) {
        a.normalize();
        b.normalize();

        Matrix3d m = Matrix3d::Identity();
        Vector3d v = a.cross(b);

        Matrix3d skew;
        skew << 0, -v[2], v[1],
                v[2], 0, -v[0],
                -v[1], v[0], 0;

        double c = a.dot(b);
        double s = v.norm();

        return Matrix3d::Identity() + skew + (skew * skew * (1 - c / (s*s)));
    }
    static Vector3d flip_vector_about(Vector3d x, Vector3d about) {
        Matrix3d align = align_vectors_matrix(x, about);
        return align * align * x;
    }
};

#endif /* end of include guard: __GEOMETRY_H__ */
