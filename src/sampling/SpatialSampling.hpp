#ifndef __SPATIALSAMPLING_H__
#define __SPATIALSAMPLING_H__

#include <Eigen/Dense>

using namespace Eigen;

class SpatialSampling {
public:
  SpatialSampling(const Vector2& domain) : _domain(domain) {};
  virtual ~SpatialSampling(){};

  virtual bool has_next() = 0;
  virtual Vector2 next() = 0;

private:
  const Vector2 _domain;
};

#endif /* end of include guard: __SPATIALSAMPLING_H__ */
