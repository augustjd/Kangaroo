#ifndef __DEPTHPATHTRACER_H__
#define __DEPTHPATHTRACER_H__

#include "Tracer.hpp"
#include "color/Color.hpp"

#define PERTURBATION 0.001

#define MINIMUM_IMPORTANCE 0.001
class DepthPathTracer : public Tracer {
public:
    DepthPathTracer(Sampler& sampler, unsigned int _depth) : Tracer(sampler), depth(_depth) {};
    virtual ~DepthPathTracer() {};

    int depth;

    virtual Color trace(const Scene& scene, ImportanceRay& first_ray) {
        Color color(0);
#ifdef DO_PERTURBATION
        Vector3d direction = (first_ray.direction() + (_sampler.random_direction() * PERTURBATION)).normalized();
        ImportanceRay ray = ImportanceRay(first_ray.origin(), direction, first_ray.importance);
#else
        ImportanceRay ray = first_ray;
#endif
        const SceneObject* last = NULL;
        for (int i = 0; i < depth; i++) {
            Intersection intersection = scene.closest_intersection(ray);
            if (intersection.isNone()) {
                break;
            }
            if (last == &intersection.object()) {
                //break;
            }
            color += 
                (ray.importance * intersection.object().material->emitted(intersection.location()))
                * fabs(ray.direction().dot(intersection.normal()));

            ray = intersection.object().next(ray, intersection, _sampler);
            last = &intersection.object();

            if (ray.importance.luminance() < MINIMUM_IMPORTANCE) {
                break;
            }
        }
        return color;
    };
};

#endif /* end of include guard: __DEPTHPATHTRACER_H__ */
