#ifndef __FORMATTING_H__
#define __FORMATTING_H__

#include <cstdio>
#include <iostream>
#include <typeinfo>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

ostream& operator<<(ostream& out, const Vector3d& obj) {
  char buffer[100];
  sprintf(buffer, "<%.2f, %.2f, %.2f>", obj[0], obj[1], obj[2]);
  return out << buffer;
}

ostream& operator<<(ostream& out, const Vector2d& obj) {
  char buffer[100];
  sprintf(buffer, "<%.2f, %.2f>", obj[0], obj[1]);
  return out << buffer;
}

#ifdef NOCOLOR
  #define BOLD_GREEN(x) x
  #define BOLD_BLUE(x)  x
#else
  #define BOLD_GREEN(x) "\033[1;32m" << (x) << "\033[0m"
  #define BOLD_BLUE(x)  "\033[1;34m" << (x) << "\033[0m"
#endif

#endif /* end of include guard: __FORMATTING_H__ */
