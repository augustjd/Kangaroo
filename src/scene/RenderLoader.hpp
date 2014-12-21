#pragma once

#include <string>
#include <memory>

#include "Scene.hpp"
#include "Render.hpp"
 
#include "xml/tinyxml2.hpp"

using std::string;

using std::vector;
using std::unique_ptr;
using namespace tinyxml2;

class RenderLoader {
public:
    static unique_ptr<Render> load_from_string(const char* s);
    static unique_ptr<Render> load_from_string(const string& s);
    static unique_ptr<Render> load_from_file(const char* s);
    static unique_ptr<Render> load_from_file(const string& s);

private:
    static unique_ptr<Scene> load_scene(const XMLElement* el);

    static unique_ptr<Camera> load_camera(const XMLElement* el, const Scene* scene);
    static unique_ptr<Camera> default_camera(const Scene* scene);

    static string load_file(const char* path);
};
