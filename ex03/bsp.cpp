#include "Point.hpp"

static Fixed calcCrossProduct(Point const &start, Point const &end,
                              Point const &point) {
  return (end.getX() - start.getX()) * (point.getY() - start.getY()) -
         (end.getY() - start.getY()) * (point.getX() - start.getX());
}

bool bsp(Point const a, Point const b, Point const c, Point const point) {
  Fixed crossAB;
  Fixed crossBC;
  Fixed crossCA;
  Fixed const zero(0);
  bool hasPositive;
  bool hasNegative;

  crossAB = calcCrossProduct(a, b, point);
  crossBC = calcCrossProduct(b, c, point);
  crossCA = calcCrossProduct(c, a, point);
  if (crossAB == zero || crossBC == zero || crossCA == zero)
    return false;
  hasPositive = crossAB > zero || crossBC > zero || crossCA > zero;
  hasNegative = crossAB < zero || crossBC < zero || crossCA < zero;
  return !(hasPositive && hasNegative);
}
