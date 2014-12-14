#include "Sampler.hpp"

std::ostream& operator<< (std::ostream& out, Sampler obj) {
  return out << "Sampler(seed=" << obj.seed() << ")";
}
