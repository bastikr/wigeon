#include "wigeon/vector1d.h"
#include "wigeon/point1d.h"


namespace wigeon {

Point1D operator+(const Point1D& point, const Vector1D& vector) {
  return Point1D(point.x() + vector.x());
}

Point1D operator+(const Vector1D& vector, const Point1D& point) {
  return Point1D(vector.x() + point.x());
}

Point1D operator-(const Point1D& point, const Vector1D& vector) {
  return Point1D(point.x() - vector.x());
}

Point1D operator-(const Vector1D& vector, const Point1D& point) {
  return Point1D(vector.x() - point.x());
}

Vector1D operator-(const Point1D& point0, const Point1D& point1) {
  return Vector1D(point0.x() - point1.x());
}

} // namespace wigeon
