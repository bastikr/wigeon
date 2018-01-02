#include "wigeon/point1d.h"
#include "wigeon/vector1d.h"


namespace wigeon {

Point1D Point1D::operator+(const Vector1D& vector) const {
  return Point1D(vector.x() + x());
}

Vector1D Point1D::operator-(const Point1D& point) const {
  return Vector1D(x()-point.x());
}

Point1D Point1D::operator-(const Vector1D& vector) const {
  return Point1D(x()-vector.x());
}

} // namespace wigeon
