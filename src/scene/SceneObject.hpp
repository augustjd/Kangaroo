#ifndef __SCENEOBJECT_H__
#define __SCENEOBJECT_H__

#include <memory>

#include "geometry/Ray.hpp"
#include "geometry/Surface.hpp"
#include "material/Material.hpp"

using std::unique_ptr;
using std::shared_ptr;

class SceneObject {
public:
    SceneObject(Surface* _surface, Material* _material);
    SceneObject(unique_ptr<Surface>& _surface, shared_ptr<Material>& _material);

    virtual ~SceneObject(){};

    const unique_ptr<Surface> surface;
    const shared_ptr<Material> material;

    Intersection intersect(const Ray& ray);

    ImportanceRay next(const ImportanceRay& incoming, const Intersection& intersection, Sampler& sampler) const;

    friend std::ostream& operator << (std::ostream& os, const SceneObject& b) {
        return os << BOLD_BLUE("SceneObject")"("
            << BOLD_GREEN("Surface")"=" << *b.surface << ", "
            << BOLD_GREEN("Material")"=" << *b.material << ")";
    }
};

#include "geometry/Intersection.hpp"

#endif /* end of include guard: __SCENEOBJECT_H__ */
