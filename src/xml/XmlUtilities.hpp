#pragma once
#ifndef __XMLUTILITIES_H__
#define __XMLUTILITIES_H__

#include "xml/tinyxml2.hpp"
#include "color/Color.hpp"
#include <Eigen/Dense>
 
using namespace tinyxml2;
using namespace Eigen;

template <typename T>
T load_xml(const XMLElement* el);

template <typename T>
T load_or_default(const XMLElement* el, T _default) {
    if (el == NULL) return _default;
    else return load_xml<T>(el);
}

template <>
Vector3d load_xml(const XMLElement* el);

template <>
Color load_xml(const XMLElement* el);

template <>
double load_xml(const XMLElement* el);

template <>
int load_xml(const XMLElement* el);

Color load_color(const XMLElement* el);


#endif /* end of include guard: __XMLUTILITIES_H__ */    
