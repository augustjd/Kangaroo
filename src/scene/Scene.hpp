#ifndef __SCENE_H__
#define __SCENE_H__

#include "SceneObject.hpp"
#include "../geometry/Ray.hpp"
#include "../geometry/Surface.hpp"
 
#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

class Scene {
    friend class SceneLoader;
public:
    Intersection closest_intersection(const Ray& ray) const;

    const vector<unique_ptr<SceneObject>>& objects() const { return _objects; };
private:
    vector<unique_ptr<SceneObject>> _objects;
};

ostream& operator<<(ostream& out, const Scene& scene);

#endif /* end of include guard: __SCENE_H__ */
