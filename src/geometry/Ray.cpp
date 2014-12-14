#include "Ray.hpp"

std::ostream& operator<< (std::ostream& out, const Ray& obj) {
  return out << BOLD_BLUE("Ray") "(" 
    << BOLD_GREEN("origin") "=" << vector_to_str(obj.origin()) << ", "
    << BOLD_GREEN("direction") "=" << vector_to_str(obj.direction()) << ")";
}
