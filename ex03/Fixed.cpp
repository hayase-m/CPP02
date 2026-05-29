#include "Fixed.hpp"
#include <climits>
#include <cmath>
#include <iostream>

// Orthodox Canonical Form
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

// Constructors
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

// Getter, setter, and conversion
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

// Comparison operators
bool Fixed::operator>(const Fixed &rhs) const {
  return _rawBits > rhs._rawBits;
}
bool Fixed::operator<(const Fixed &rhs) const {
  return _rawBits < rhs._rawBits;
}
bool Fixed::operator>=(const Fixed &rhs) const {
  return _rawBits >= rhs._rawBits;
}
bool Fixed::operator<=(const Fixed &rhs) const {
  return _rawBits <= rhs._rawBits;
}
bool Fixed::operator==(const Fixed &rhs) const {
  return _rawBits == rhs._rawBits;
}
bool Fixed::operator!=(const Fixed &rhs) const {
  return _rawBits != rhs._rawBits;
}

// Arithmetic operators
Fixed Fixed::operator+(const Fixed &rhs) const {
  Fixed result;
  if (rhs._rawBits > 0 && _rawBits > INT_MAX - rhs._rawBits)
    result._rawBits = INT_MAX;
  else if (rhs._rawBits < 0 && _rawBits < INT_MIN - rhs._rawBits)
    result._rawBits = INT_MIN;
  else
    result._rawBits = _rawBits + rhs._rawBits;
  return result;
}

Fixed Fixed::operator-(const Fixed &rhs) const {
  Fixed result;
  if (rhs._rawBits < 0 && _rawBits > INT_MAX + rhs._rawBits)
    result._rawBits = INT_MAX;
  else if (rhs._rawBits > 0 && _rawBits < INT_MIN + rhs._rawBits)
    result._rawBits = INT_MIN;
  else
    result._rawBits = _rawBits - rhs._rawBits;
  return result;
}

Fixed Fixed::operator*(const Fixed &rhs) const {
  Fixed result;
  long rawResult;

  rawResult = static_cast<long>(_rawBits) * static_cast<long>(rhs._rawBits);
  rawResult /= (1 << _fractionalBits);
  if (rawResult > INT_MAX)
    result._rawBits = INT_MAX;
  else if (rawResult < INT_MIN)
    result._rawBits = INT_MIN;
  else
    result._rawBits = static_cast<int>(rawResult);
  return result;
}

Fixed Fixed::operator/(const Fixed &rhs) const {
  Fixed result;
  long rawResult;

  rawResult = static_cast<long>(_rawBits) * (1L << _fractionalBits) /
              static_cast<long>(rhs._rawBits);
  if (rawResult > INT_MAX)
    result._rawBits = INT_MAX;
  else if (rawResult < INT_MIN)
    result._rawBits = INT_MIN;
  else
    result._rawBits = static_cast<int>(rawResult);
  return result;
}

// Increment and decrement operators
Fixed &Fixed::operator++(void) {
  if (_rawBits < INT_MAX)
    _rawBits++;
  return *this;
}

Fixed Fixed::operator++(int) {
  Fixed result;
  result._rawBits = _rawBits;
  if (_rawBits < INT_MAX)
    _rawBits++;
  return result;
}

Fixed &Fixed::operator--(void) {
  if (_rawBits > INT_MIN)
    _rawBits--;
  return *this;
}

Fixed Fixed::operator--(int) {
  Fixed result;
  result._rawBits = _rawBits;
  if (_rawBits > INT_MIN)
    _rawBits--;
  return result;
}

// Min and max
Fixed &Fixed::min(Fixed &lhs, Fixed &rhs) {
  if (lhs._rawBits <= rhs._rawBits)
    return lhs;
  return rhs;
}

const Fixed &Fixed::min(const Fixed &lhs, const Fixed &rhs) {
  if (lhs._rawBits <= rhs._rawBits)
    return lhs;
  return rhs;
}

Fixed &Fixed::max(Fixed &lhs, Fixed &rhs) {
  if (lhs._rawBits >= rhs._rawBits)
    return lhs;
  return rhs;
}

const Fixed &Fixed::max(const Fixed &lhs, const Fixed &rhs) {
  if (lhs._rawBits >= rhs._rawBits)
    return lhs;
  return rhs;
}

// Insertion operator
std::ostream &operator<<(std::ostream &os, const Fixed &fixed) {
  os << fixed.toFloat();
  return os;
}
