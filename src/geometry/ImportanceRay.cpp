#include "ImportanceRay.hpp"

std::ostream& operator<< (std::ostream& out, const ImportanceRay& obj) {
  return out << BOLD_BLUE("ImportanceRay") "(" 
    << BOLD_GREEN("origin") "=" << obj.origin() << ", "
    << BOLD_GREEN("direction") "=" << obj.direction() << ", "
    << BOLD_GREEN("importance") "=" << obj.importance << ")";
}
