#ifndef __SAMPLER_H__
#define __SAMPLER_H__

#include <cstdlib>
#include <ctime>

#include "../Constants.hpp"
#include "../geometry/Geometry.hpp"
 

class Sampler {
public:
  Sampler() : _seed(time(NULL)) { initialize(); };
  Sampler(long int seed) : _seed(seed) { initialize(); };


  virtual ~Sampler() {};

 double random() { return erand48(xsubi); };
 double random(double max) { return random() * max; };
 double random(double min, double max) { return min + random() * (max - min); };
 int    random_int() { return rand(); };
 int    random_int(int max) { return rand() % max; };
 int    random_int(int min, int max) { return min + rand() % (max - min); };

 Vector3d random_direction() { 
   // http://mathworld.wolfram.com/SpherePointPicking.html
   double u     = random(-1.0, 1.0);
   double theta = random(Constants::TWO_PI);

   return Vector3d(
       sqrt(1 - u*u) * cos(theta),
       sqrt(1 - u*u) * sin(theta),
       u
     ).normalized();
 };

 Vector3d random_direction_in_hemisphere() { 
     Vector3d v = random_direction();
     v.y() = fabs(v.y());
     return v;
 }
 Vector3d random_direction_in_hemisphere(const Vector3d& pole) {
     return Geometry::align_vectors_matrix(Vector3d(0, 1, 0), pole.normalized()) * random_direction_in_hemisphere();
 }

 unsigned long seed() { return _seed; };
private:
  void initialize() {
    xsubi[0] = ((unsigned short*)&_seed)[0];
    xsubi[1] = ((unsigned short*)&_seed)[1];
    xsubi[2] = ((unsigned short*)&_seed)[2];

    srand((unsigned int)_seed); 
    srandom(_seed); 
  }
  unsigned long _seed;
  unsigned short xsubi[3];
};

std::ostream& operator<< (std::ostream& out, Sampler obj);
#endif /* end of include guard: __SAMPLER_H__ */
