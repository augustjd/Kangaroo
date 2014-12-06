#ifndef __SCENE_H__
#define __SCENE_H__

class Scene {
public:
    Scene() {};
    Scene() {};
    virtual ~Scene(){};

private:
    vector<SceneObject> objects;
};

#endif /* end of include guard: __SCENE_H__ */
