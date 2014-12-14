#include "Intersection.hpp"
 
ostream& operator<< (ostream& out, const Intersection& obj) {
  if (obj.isNone()) {
    return out << BOLD_BLUE("Intersection")"(none)";
  } else if (obj._object == NULL) {
    return out << BOLD_BLUE("Intersection") << "("
      << BOLD_GREEN("location") << "=" << vector_to_str(obj._location) << ", "
      << BOLD_GREEN("object") << "=NULL)";
  } else {
    return out << BOLD_BLUE("Intersection") << "("
      << BOLD_GREEN("location") << "=" << vector_to_str(obj._location) << ", "
      << BOLD_GREEN("object") << "=" << *obj._object << ")";
  }
}
