#include "wigeon/vector1d.h"

#include <cmath>

namespace wigeon {

double Vector1D::length2() const {
  return x()*x();
}

double Vector1D::length() const {
  return abs(x());
}

Point1D Vector1D::operator+(Point1D point) const {
  point.data[0] += data[0];
  return point;
}

Vector1D Vector1D::operator-() const {
  return Vector1D(-x());
}

Point1D Vector1D::operator-(Point1D point) const {
  point.data[0] -= data[0];
  return point;
}

Vector1D Vector1D::operator+(Vector1D vector) const {
  vector.data[0] += data[0];
  return vector;
}

Vector1D Vector1D::operator*(double a) const {
  return Vector1D(a*x());
}

double Vector1D::operator*(const Vector1D& vector) const {
  return vector.x()*x();
}

Vector1D Vector1D::operator/(double a) const {
  return Vector1D(x()/a);
}

} // namepsace wigeon
