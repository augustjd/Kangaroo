#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

class Constants {
public:
  static constexpr double PI = 3.14159265359;
  static constexpr double TWO_PI = 6.2831853071795864769252867665590057683943387987502116;
  static constexpr double PI_OVER_TWO = 1.570796326794896619231321691639751442098584699687552910487472;

  static inline double degrees_to_radians(double deg) {
      return deg * 0.017453292519943295769236907684886127134428718885417254560971;
  }
};

#endif /* end of include guard: __CONSTANTS_H__ */
