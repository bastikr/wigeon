#include "wigeon/vector1d.h"
#include "wigeon/point1d.h"

#include <cmath>

namespace wigeon {

Vector1D::Vector1D(const Point1D& p)
    : data(p.data) {}

Vector1D::Vector1D(double x)
    : data({{x}}) {}

double Vector1D::x() const {
  return data[0];
}

void Vector1D::set_x(double x) {
  data[0] = x;
}

double Vector1D::length2() const {
  return x()*x();
}

double Vector1D::length() const {
  return std::abs(x());
}


Vector1D operator+(const Vector1D& vector0, const Vector1D& vector1) {
  return Vector1D(vector0.x() + vector1.x());
}


Vector1D operator-(const Vector1D& vector) {
  return Vector1D(-vector.x());
}

Vector1D operator-(const Vector1D& vector0, const Vector1D& vector1) {
  return Vector1D(vector0.x() - vector1.x());
}


Vector1D operator*(const Vector1D& vector, double a) {
  return Vector1D(vector.x()*a);
}

Vector1D operator*(double a, const Vector1D& vector) {
  return Vector1D(a*vector.x());
}

double operator*(const Vector1D& vector0, const Vector1D& vector1) {
  return vector0.x()*vector1.x();
}


Vector1D operator/(const Vector1D& vector, double a) {
  return Vector1D(vector.x()/a);
}

} // namepsace wigeon
