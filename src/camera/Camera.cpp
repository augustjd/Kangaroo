#include "Camera.hpp"

unique_ptr<Camera> Camera::load_from_xml(const XMLElement* el, const Scene* scene) {
    auto position = load_or_default<Vector3d>(el->FirstChildElement("position"), Vector3d(0,0,0));

    auto direction = load_or_default<Vector3d>(el->FirstChildElement("direction"), Vector3d(0,0,1));

    auto up = load_or_default<Vector3d>(el->FirstChildElement("up"), Vector3d(0,1,0));

    double fovx = load_or_default<double>(el->FirstChildElement("fovx"), 45);

    size_t width  = 800;
    size_t height = 600;

    const XMLElement* image_element = el->FirstChildElement("image");
    if (image_element) {
        width = image_element->DoubleAttribute("width");
        height = image_element->DoubleAttribute("height");
    }

    size_t passes = load_or_default<int>(el->FirstChildElement("passes"), 20);

    shared_ptr<sf::Image> image = shared_ptr<sf::Image>(new sf::Image());
    image->create(width, height, sf::Color(0,70,128));

    return unique_ptr<Camera>(new Camera(passes, position, up, direction, image, fovx, *scene));
}
