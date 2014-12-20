#include <streambuf>
#include <fstream>
#include <map>

#include "SceneLoader.hpp"
#include "SceneObject.hpp"
#include "Formatting.hpp"
#include "geometry/Sphere.hpp"
#include "geometry/Triangle.hpp"
#include "color/Color.hpp"

#include "material/Material.hpp"
#include "material/LambertianMaterial.hpp"
#include "material/SpecularMaterial.hpp"
#include "material/TransparentSpecularMaterial.hpp"
 
#include "xml/tinyxml2.hpp"

using namespace std;
using namespace tinyxml2;


static Vector3d load_vector(const XMLElement* el) {
    return Vector3d(el->DoubleAttribute("x"),
                    el->DoubleAttribute("y"),
                    el->DoubleAttribute("z"));
}

static Color load_color(const XMLElement* el) {
    return Color(el->DoubleAttribute("r"),
                 el->DoubleAttribute("g"),
                 el->DoubleAttribute("b"));
}

struct MaterialLoader {
    virtual Material* load(const XMLElement* el) = 0;
};

struct TransparentSpecularMaterialLoader : MaterialLoader {
    virtual Material* load(const XMLElement* el) {
        const XMLElement* color_node = el->FirstChildElement("color");
        const XMLElement* emit_node = el->FirstChildElement("emit");
        const XMLElement* opacity_node = el->FirstChildElement("opacity");
        Color color;
        Color emit;
        double opacity = 1.0;
        if (opacity_node != NULL) {
            opacity_node->QueryDoubleText(&opacity);
        }
        if (color_node != NULL) {
            color = load_color(color_node);
        } else {
            color = Color(1.0);
        }

        if (emit_node != NULL) {
            emit = load_color(emit_node);
        } else {
            emit = Color(0);
        }

        return new TransparentSpecularMaterial(color, emit, opacity);
    }
};

struct SpecularMaterialLoader : MaterialLoader {
    virtual Material* load(const XMLElement* el) {
        const XMLElement* color_node = el->FirstChildElement("color");

        Color color;
        if (color_node != NULL) {
            color = load_color(color_node);
        } else {
            color = Color(1.0);
        }

        return new SpecularMaterial(color);
    }
};

struct LambertianMaterialLoader : MaterialLoader{
    virtual Material* load(const XMLElement* el) {
        const XMLElement* color_node = el->FirstChildElement("color");
        const XMLElement* emit_node = el->FirstChildElement("emit");

        Color color;
        Color emit;
        if (color_node != NULL) {
            color = load_color(color_node);
        } else {
            color = Color(1.0);
        }

        if (emit_node != NULL) {
            emit = load_color(emit_node);
        } else {
            emit = Color(0);
        }

        return new LambertianMaterial(color, emit);
    }
};

static std::map<string, MaterialLoader*> material_loaders = {
    { "Lambertian", new LambertianMaterialLoader() },
    { "Specular", new SpecularMaterialLoader() },
    { "TransparentSpecular", new TransparentSpecularMaterialLoader() },
};

struct SceneObjectLoader {
    SceneObject* load(const XMLElement* el) { 
        Material* material;
        const XMLElement* material_node = el->FirstChildElement("material");
        if (material_node == NULL) {
            material = new LambertianMaterial();
        } else {
            string material_name(material_node->FirstChildElement("type")->GetText());

            auto match = material_loaders.find(material_name);
            if (match == material_loaders.end()) {
                cout << "No material with name " << BOLD_GREEN(material_name) << " found." << endl;
                material = new LambertianMaterial();
            } else {
                cout << "Loading " << BOLD_GREEN(material_name) << "..." << endl;
                material = match->second->load(material_node); 
            }
        }

        return new SceneObject(static_cast<Surface*>(load_surface(el)), material);
    }
    virtual Surface* load_surface(const XMLElement* el) = 0;
};

struct SphereLoader : SceneObjectLoader {
    Sphere* load_surface(const XMLElement* el) {
        return new Sphere(load_vector(el->FirstChildElement("position")), el->DoubleAttribute("r"));
    }
};

struct TriangleLoader : SceneObjectLoader {
    Triangle* load_surface(const XMLElement* el) {
        const XMLElement* point_iterator = el->FirstChildElement("point");

        Vector3d v1 = load_vector(point_iterator);
        Vector3d v2 = load_vector(point_iterator->NextSiblingElement());
        Vector3d v3 = load_vector(point_iterator->NextSiblingElement()->NextSiblingElement());

        return new Triangle(v1, v2, v3);
    }
};

static std::map<string, SceneObjectLoader*> object_loaders = {
    { "sphere", static_cast<SceneObjectLoader*>(new SphereLoader()) },
    { "triangle", static_cast<SceneObjectLoader*>(new TriangleLoader()) },
};


template <typename K, typename V>
bool contains(std::map<K,V> m, K key) {
    return m.find(key) != m.end();
}

unique_ptr<Scene> SceneLoader::load_from_string(const char* s) {
    XMLDocument doc;
    doc.Parse(s);
    if (doc.ErrorID() != 0) {
        FATAL("Failed to parse input string as XML: " << endl << s);
    }

    XMLElement* root = doc.RootElement();
    if (!root->FirstChildElement("scene")) {
        FATAL("Scene file missing <scene> tag.");
    }

    XMLElement* scene_root = root->FirstChildElement("scene");

    vector<SceneObject*> objects;
    for (XMLElement* node = scene_root->FirstChildElement();
         node != NULL; 
         node = node->NextSiblingElement()) {
        string tag(node->Name());
        if (contains(object_loaders, tag)) {
            objects.push_back(object_loaders.find(tag)->second->load(node));
        }

    }

    return unique_ptr<Scene>(new Scene(objects));
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
