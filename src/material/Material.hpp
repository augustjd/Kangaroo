#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "geometry/ImportanceRay.hpp"
#include "sampling/Sampler.hpp"
#include "color/Color.hpp"
 
#include "Formatting.hpp"
 

class Material {
public:
  Material() {};
  virtual ~Material () {};

  virtual ImportanceRay next(const ImportanceRay& incoming, const Vector3d& position, const Vector3d& normal, Sampler& sampler) = 0;
  virtual bool is_emitter() const = 0;

  virtual Color reflected(const Vector3d& position) const = 0;
  virtual Color emitted(const Vector3d& position) const = 0;

  friend std::ostream& operator << (std::ostream& os, const Material& b) {
      return b.print(os);
  }
protected:
  virtual std::ostream& print(std::ostream&) const = 0;
};

class ConstantColorMaterial : public Material {
public:
    ConstantColorMaterial(const Color& reflected, const Color& emitted) : 
        _reflected(reflected), _emitted(emitted) {};

    virtual Color reflected(const Vector3d& position) const { return _reflected; };
    virtual Color emitted(const Vector3d& position) const { return _emitted; };

    virtual Color reflected() const { return _reflected; };
    virtual Color emitted() const { return _emitted; };

    virtual bool is_emitter() const { return _emitted.luminance() > 0.0; };

protected:
    Color _reflected;
    Color _emitted;
};

#endif /* end of include guard: __MATERIAL_H__ */
