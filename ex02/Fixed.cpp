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

Fixed::Fixed(const int value) : _rawBits(value * (1 << _fractionalBits)) {
  std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(const float value)
    : _rawBits(static_cast<int>(roundf(value * (1 << _fractionalBits)))) {
  std::cout << "Float constructor called" << std::endl;
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

std::ostream &operator<<(std::ostream &os, const Fixed &fixed) {
  os << fixed.toFloat();
  return os;
}
