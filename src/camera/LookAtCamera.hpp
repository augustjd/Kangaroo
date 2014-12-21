#ifndef __LOOKATCAMERA_H__
#define __LOOKATCAMERA_H__

#include "Camera.hpp"

class LookAtCamera : public Camera {
public:
    LookAtCamera(size_t passes, Vector3d position, Vector3d up, Vector3d at,
                 shared_ptr<sf::Image>& image, double fovx, const Scene& scene) :
        Camera(passes, position, up, (at - position).normalized(), image, fovx, scene), _at(at), _theta(0), _phi(0) {};

    virtual ~LookAtCamera(){};

private:
    Vector3d _at;
    double _theta;
    double _phi;
    
};

#endif /* end of include guard: __LOOKATCAMERA_H__ */
