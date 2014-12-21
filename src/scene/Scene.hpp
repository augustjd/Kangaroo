#ifndef __SCENE_H__
#define __SCENE_H__

#include "geometry/Intersection.hpp"
 
#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;

class Scene {
    friend class RenderLoader;
public:
    Scene() {
    }

    Scene(const vector<SceneObject*>& objects) {
        for (auto& obj : objects) {
            _objects.emplace_back(obj);
            if (obj->material->is_emitter()) {
                _emitters.emplace_back(obj);
            }
        }
    }

    Intersection closest_intersection(const Ray& ray) const;

    const vector<SceneObject*>& objects() const { return _objects; };
private:
    vector<SceneObject*> _objects;
    vector<SceneObject*> _emitters;
};

ostream& operator<<(ostream& out, const Scene& scene);

#endif /* end of include guard: __SCENE_H__ */
