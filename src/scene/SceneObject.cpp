#include "SceneObject.hpp"

SceneObject::SceneObject(Surface* _surface, Material* _material) : 
    surface(unique_ptr<Surface>(_surface)), material(shared_ptr<Material>(_material)) 
{};

SceneObject::SceneObject(unique_ptr<Surface>& _surface, shared_ptr<Material>& _material) : 
    surface(std::move(_surface)), material(std::move(_material)) 
{};

Intersection SceneObject::intersect(const Ray& ray) { 
    return surface->intersect(ray).set_object(*this);
};

ImportanceRay SceneObject::next(const Ray& incoming, const Intersection& intersection, Sampler& sampler) const {
    return material->next(incoming, intersection.location(), intersection.normal(), sampler);
}
