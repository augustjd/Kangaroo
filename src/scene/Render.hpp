#ifndef __RENDER_H__
#define __RENDER_H__

#include "scene/Scene.hpp"
#include "camera/Camera.hpp"

#include <memory>

using std::unique_ptr;

struct Render {
    unique_ptr<Scene> scene;
    unique_ptr<Camera> camera;
};

#endif /* end of include guard: __RENDER_H__ */
