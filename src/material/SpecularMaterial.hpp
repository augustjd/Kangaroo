#pragma once

#include "sampling/Sampler.hpp"
#include "Constants.hpp"
#include "BRDFMaterial.hpp"
#include "geometry/Geometry.hpp"
 
struct SpecularBRDF : public BRDF {
    SpecularBRDF(const Color& _reflected) : reflected(_reflected) {};
    const Color& reflected;
    virtual AngleSample sample(double theta_in, Sampler& sampler);
};

class SpecularMaterial : public BRDFMaterial {
public:
  SpecularMaterial(Color reflected) : BRDFMaterial(new SpecularBRDF(reflected)), _reflected(reflected) {};
  SpecularMaterial() : BRDFMaterial(new SpecularBRDF(Color(0.5))), _reflected(Color(0.5)) {};
  virtual ~SpecularMaterial() {};

  virtual Color reflected(const Vector3d& position) const {
      return _reflected;
  }
  virtual Color reflected() const {
      return _reflected;
  }
  virtual Color emitted(const Vector3d& position) const {
      return Color(0.0);
  }
  virtual Color emitted() const {
      return Color(0.0);
  }
  virtual bool is_emitter() const { return false; };

  virtual std::ostream& print(std::ostream& os) const {
      return os << BOLD_BLUE("SpecularMaterial") "(" 
          << BOLD_GREEN("reflected")"=" << reflected()
          << BOLD_GREEN("emitted")"=" << emitted()
          << ")";
  }
private:
  Color _reflected;
};  
