#include "Point.hpp"
#include <iostream>

int main(void) {
  Point a(0.0f, 0.0f);
  Point b(10.0f, 0.0f);
  Point c(0.0f, 10.0f);
  bool inside;
  bool outside;
  bool edge;

  inside = bsp(a, b, c, Point(1.0f, 1.0f));
  outside = bsp(a, b, c, Point(10.0f, 10.0f));
  edge = bsp(a, b, c, Point(5.0f, 0.0f));
  std::cout << std::boolalpha;
  std::cout << "inside: " << inside << std::endl;
  std::cout << "outside: " << outside << std::endl;
  std::cout << "edge: " << edge << std::endl;
  if (inside && !outside && !edge)
    return 0;
  return 1;
}
