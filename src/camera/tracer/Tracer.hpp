#ifndef __TRACER_H__
#define __TRACER_H__

#include "scene/Scene.hpp"
#include "geometry/ImportanceRay.hpp"

class Tracer {
public:
    Tracer(Sampler& sampler) : _sampler(sampler) {};
    virtual ~Tracer() {};
    virtual Color trace(const Scene& scene, ImportanceRay& ray) = 0;

protected:
    Sampler& _sampler;
};

#endif /* end of include guard: __TRACER_H__ */
