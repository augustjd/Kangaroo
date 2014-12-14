#include "Sphere.hpp"

string vector_to_str(const Vector3d& obj) {
  char buffer[64];
  sprintf(buffer, "<%.2f, %.2f, %.2f>", obj[0], obj[1], obj[2]);
  return buffer;
}
