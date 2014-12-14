#ifndef __SCENELOADER_H__
#define __SCENELOADER_H__

#include "Scene.hpp"

#include <string>
#include <memory>

using std::string;

using std::vector;
using std::unique_ptr;

struct SceneLoader {
    static unique_ptr<Scene> load_from_string(const char* s);
    static unique_ptr<Scene> load_from_string(const string& s);
    static unique_ptr<Scene> load_from_file(const char* s);
    static unique_ptr<Scene> load_from_file(const string& s);

private:
    static string load_file(const char* path);
};

#endif /* end of include guard: __SCENELOADER_H__ */
