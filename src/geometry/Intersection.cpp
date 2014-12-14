#include "Intersection.hpp"
 
ostream& operator<< (ostream& out, const Intersection& obj) {
  if (obj.isNone()) {
    return out << BOLD_BLUE("Intersection")"(none)";
  } else {
    return out << BOLD_BLUE("Intersection") << "("
      << BOLD_GREEN("location") << "=" << vector_to_str(obj._location) << ", "
      << BOLD_GREEN("surface") << "=" << *obj._surface << ")";
  }
}