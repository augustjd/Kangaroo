#ifndef __FORMATTING_H__
#define __FORMATTING_H__

#include <cstdio>
#include <iostream>
#include <typeinfo>
#include <memory>
#include <vector>

#include <Eigen/Dense>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace Eigen;

#ifdef NOCOLOR
  #define BOLD_GREEN(x) x
  #define BOLD_BLUE(x)  x
  #define BOLD_RED(x)   x
  #define GREEN(x)      x
  #define BLUE(x)       x
  #define RED(x)        x
#else
  #define BOLD_GREEN(x) "\033[1;32m" << x << "\033[0m"
  #define BOLD_BLUE(x)  "\033[1;34m" << x << "\033[0m"
  #define BOLD_RED(x)   "\033[1;31m" << x << "\033[0m"
  #define GREEN(x)      "\033[32m" << x << "\033[0m"
  #define BLUE(x)       "\033[34m" << x << "\033[0m"
  #define RED(x)        "\033[31m" << x << "\033[0m"
#endif

#define FATAL(msg) do { std::cerr << BOLD_RED("FATAL ERROR(") << RED(__FILENAME__ " in " << &*__FUNCTION__) << BOLD_RED("): ") << msg << std::endl; exit(1); } while (0)

string vector_to_str(const Vector3d& obj);
string vector_to_str(const Vector2d& obj);

ostream& operator<<(ostream& out, const sf::Color& obj);

template <typename T>
ostream& operator<<(ostream& out, const vector<T>& obj);

template <typename T>
ostream& operator<<(ostream& out, const vector<unique_ptr<T>>& obj);


#define DEBUG_PRINT(expr) cout << #expr << ": " << (expr) << endl;
#endif /* end of include guard: __FORMATTING_H__ */
