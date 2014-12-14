#include <streambuf>
#include <fstream>
#include <map>

#include "SceneLoader.hpp"
#include "SceneObject.hpp"
#include "Formatting.hpp"
#include "geometry/Sphere.hpp"

#include "material/Material.hpp"
#include "material/LambertianMaterial.hpp"
 
#include "xml/tinyxml2.hpp"
#include "/home/august/Homework/acg/final_project/src/xml/tinyxml2.hpp"
#include "/home/august/Homework/acg/final_project/src/geometry/Sphere.hpp"
#include "/home/august/Homework/acg/final_project/src/material/Material.hpp"
#include "/home/august/Homework/acg/final_project/src/material/LambertianMaterial.hpp"

using namespace std;
using namespace tinyxml2;


static Vector3d load_vector(const XMLElement* el) {
    return Vector3d(el->DoubleAttribute("x"),
                    el->DoubleAttribute("y"),
                    el->DoubleAttribute("z"));
}

struct MaterialLoader {
    virtual Material* load(const XMLElement* el) = 0;
};

static std::map<string, MaterialLoader*> material_loaders = {
};

struct SceneObjectLoader {
    virtual SceneObject* load(const XMLElement* el) = 0;
};

struct SphereLoader : SceneObjectLoader {
    Sphere* load_surface(const XMLElement* el) {
        return new Sphere(load_vector(el->FirstChildElement("position")), el->DoubleAttribute("r"));
    }

    SceneObject* load(const XMLElement* el) { 
        Material* material;
        const XMLElement* material_node = el->FirstChildElement("material");
        if (material_node == NULL) {
            material = new LambertianMaterial();
        } else {
            material_loaders.find(material_node->Name())->second->load(material_node); 
        }

        return new SceneObject(static_cast<Surface*>(load_surface(el)), material);
    }
};

static std::map<string, SceneObjectLoader*> object_loaders = {
    { string("sphere"), static_cast<SceneObjectLoader*>(new SphereLoader()) }
};


template <typename K, typename V>
bool contains(std::map<K,V> m, K key) {
    return m.find(key) != m.end();
}

unique_ptr<Scene> SceneLoader::load_from_string(const char* s) {
    unique_ptr<Scene> result = unique_ptr<Scene>(new Scene());
    XMLDocument doc;
    doc.Parse(s);
    if (doc.ErrorID() != 0) {
        FATAL("Failed to parse input string as XML: " << endl << s);
    }

    XMLElement* root = doc.RootElement();

    for (XMLElement* node = root->FirstChildElement();
         node != NULL; 
         node = node->NextSiblingElement()) {
        string tag(node->Name());
        if (contains(object_loaders, tag)) {
            result->_objects.emplace_back(object_loaders.find(tag)->second->load(node));
        }

    }

    return result;
}

unique_ptr<Scene> SceneLoader::load_from_string(const string& s) {
    return load_from_string(s.c_str());
}

unique_ptr<Scene> SceneLoader::load_from_file(const char* path) {
    return load_from_string(load_file(path));
}

unique_ptr<Scene> SceneLoader::load_from_file(const string& path) {
    return load_from_string(load_file(path.c_str()));
}

inline static size_t size_of_file(ifstream& f) {
    size_t size;

    f.seekg(0, ios::end);   
    size = f.tellg();
    f.seekg(0, ios::beg);

    return size;
}

string SceneLoader::load_file(const char* path) {
    using namespace std;

    ifstream f(path);
    if (!f.good()) {
        FATAL("File " << BOLD_GREEN(path) << " does not exist.");
    }
    string result;

    result.reserve(size_of_file(f));

    result.assign(istreambuf_iterator<char>(f), istreambuf_iterator<char>());

    return result;
}
