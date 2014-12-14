#include "Scene.hpp"
#include "Formatting.hpp"

Intersection Scene::closest_intersection(const Ray& ray) const {
    Intersection closest = Intersection::None();

    for (auto& obj : _objects) {
        Intersection i = obj->intersect(ray);
        if (i < closest) {
            closest = i;
        }
    }

    return closest;
}

ostream& operator<<(ostream& out, const Scene& obj) {
    out << BOLD_BLUE("Scene")"(" << BOLD_GREEN("objects") "=";

    out << '[';
    bool first = true;
    for (auto& it : obj.objects()) {
        if (!first) {
            out << ", ";
        }
        out << (SceneObject&)*it;
        first = false;
    }
    out << ']';

    return out << ")";
}
