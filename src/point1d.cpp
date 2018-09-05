#include "wigeon/vector1d.h"
#include "wigeon/point1d.h"


namespace wigeon {

Point1D::Point1D(double x)
  : data({{x}}) {}

Point1D::Point1D(const Vector1D& v)
  : data(v.data) {}

double Point1D::x() const {
  return data[0];
}

void Point1D::set_x(double x) {
  data[0] = x;
}

Point1D operator+(const Point1D& point, const Vector1D& vector) {
  return Point1D(point.x() + vector.x());
}

Point1D operator+(const Vector1D& vector, const Point1D& point) {
  return Point1D(vector.x() + point.x());
}

Point1D operator-(const Point1D& point, const Vector1D& vector) {
  return Point1D(point.x() - vector.x());
}

Vector1D operator-(const Point1D& point0, const Point1D& point1) {
  return Vector1D(point0.x() - point1.x());
}

} // namespace wigeon
