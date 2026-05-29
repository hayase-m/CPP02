#include "Fixed.hpp"
#include <climits>
#include <cmath>
#include <iostream>

Fixed::Fixed(void) : _rawBits(0) {
  std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &other) : _rawBits(other._rawBits) {
  std::cout << "Copy constructor called" << std::endl;
}

Fixed &Fixed::operator=(const Fixed &other) {
  std::cout << "Copy assignment operator called" << std::endl;
  if (this != &other)
    this->_rawBits = other._rawBits;
  return *this;
}

Fixed::~Fixed(void) { std::cout << "Destructor called" << std::endl; }

Fixed::Fixed(const int value) {
  std::cout << "Int constructor called" << std::endl;
  if (value > INT_MAX / (1 << _fractionalBits))
    _rawBits = INT_MAX;
  else if (value < INT_MIN / (1 << _fractionalBits))
    _rawBits = INT_MIN;
  else
    _rawBits = value * (1 << _fractionalBits);
}

Fixed::Fixed(const float value) {
  std::cout << "Float constructor called" << std::endl;
  float rawFloat = roundf(value * (1 << _fractionalBits));
  if (rawFloat >= static_cast<float>(INT_MAX))
    _rawBits = INT_MAX;
  else if (rawFloat < static_cast<float>(INT_MIN))
    _rawBits = INT_MIN;
  else
    _rawBits = static_cast<int>(rawFloat);
}

int Fixed::getRawBits(void) const {
  std::cout << "getRawBits member function called" << std::endl;
  return _rawBits;
}

void Fixed::setRawBits(int const raw) { _rawBits = raw; }

int Fixed::toInt(void) const { return _rawBits / (1 << _fractionalBits); }

float Fixed::toFloat(void) const {
  float rawFloat = static_cast<float>(_rawBits);
  return rawFloat / (1 << _fractionalBits);
}

std::ostream &operator<<(std::ostream &os, const Fixed &fixed) {
  os << fixed.toFloat();
  return os;
}
