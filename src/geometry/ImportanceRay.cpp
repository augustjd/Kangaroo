#include "ImportanceRay.hpp"

std::ostream& operator<< (std::ostream& out, const ImportanceRay& obj) {
  return out << BOLD_BLUE("ImportanceRay") "(" 
    << BOLD_GREEN("origin") "=" << vector_to_str(obj.origin()) << ", "
    << BOLD_GREEN("direction") "=" << vector_to_str(obj.direction()) << ", "
    << BOLD_GREEN("importance") "=" << obj.importance << ")";
}
