#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed {
private:
  int _rawBits;
  static const int _fractionalBits = 8;

public:
  Fixed(void);
  Fixed(const Fixed &other);
  Fixed &operator=(const Fixed &other);
  ~Fixed(void);

  Fixed(const int value);
  Fixed(const float value);

  int getRawBits(void) const;
  void setRawBits(int const raw);

  int toInt(void) const;
  float toFloat(void) const;
};

std::ostream &operator<<(std::ostream &os, const Fixed &fixed);

#endif
