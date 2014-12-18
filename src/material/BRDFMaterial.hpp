#pragma once

#include <memory>

#include "Material.hpp"
 

using std::unique_ptr;
 
struct AngleSample {
    // the altitude angle
    double theta;

    // the azimuth angle, relative to the incoming angle
    double phi;

    // the value associated with this pair of angles according to the BRDF
    double importance;
};

struct BRDF {
    // assumes that phi_in is 0, i.e. phi in sample is relative to incoming
    // ray.
    virtual AngleSample sample(double theta_in, Sampler& sampler) = 0;
};

class BRDFMaterial : Material {
public:
  BRDFMaterial(BRDF* brdf) : _brdf(brdf) {};
  BRDFMaterial(unique_ptr<BRDF> brdf) : _brdf(std::move(brdf)) {};
  virtual ~BRDFMaterial () {};

  virtual ImportanceRay next(const ImportanceRay& incoming, const Vector3d& position, const Vector3d& normal, Sampler& sampler);
  virtual bool is_emitter() const = 0;
  virtual Color emission() const = 0;

protected:
  virtual std::ostream& print(std::ostream&) const = 0;

  unique_ptr<BRDF> _brdf;
};
