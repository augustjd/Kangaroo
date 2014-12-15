#include "Color.hpp"

ostream& operator<<(ostream& out, const Color& color) {
    return out << "<" << RED(color.x()) << ", " << GREEN(color.y()) << ", " << BLUE(color.z()) << ">";
}
