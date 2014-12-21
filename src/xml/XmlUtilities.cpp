#include "XmlUtilities.hpp"

template <>
Vector3d load_xml(const XMLElement* el) {
    return Vector3d(el->DoubleAttribute("x"),
                    el->DoubleAttribute("y"),
                    el->DoubleAttribute("z"));
}

template <>
Color load_xml(const XMLElement* el) {
    return Color(el->DoubleAttribute("r"),
                 el->DoubleAttribute("g"),
                 el->DoubleAttribute("b"));
}

template <>
double load_xml(const XMLElement* el) {
    double val;
    el->QueryDoubleText(&val);
    return val;
}

template <>
int load_xml(const XMLElement* el) {
    int val;
    el->QueryIntText(&val);
    return val;
}

Color load_color(const XMLElement* el) {
    return load_xml<Color>(el);
}
