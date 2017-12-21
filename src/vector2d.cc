#include "geomalia/vector2d.h"

#include <cmath>

namespace geomalia {

double Vector2D::length2() const {
  return x()*x() + y()*y();
}

double Vector2D::length() const {
  return sqrt(length2());
}

Point2D Vector2D::operator+(Point2D point) const {
  point.data[0] += data[0];
  point.data[1] += data[1];
  return point;
}

Vector2D Vector2D::operator-() const {
  return Vector2D(-x(), -y());
}

Vector2D Vector2D::operator+(Vector2D vector) const {
  vector.data[0] += data[0];
  vector.data[1] += data[1];
  return vector;
}

Vector2D Vector2D::operator*(double a) const {
  return Vector2D(a*x(), a*y());
}

double Vector2D::operator*(const Vector2D& vector) const {
  return vector.x()*x() + vector.y()*y();
}

Vector2D Vector2D::operator/(double a) const {
  return Vector2D(x()/a, y()/a);
}

double cross(const Vector2D& vector0, const Vector2D& vector1) {
  return vector0.x()*vector1.y() - vector0.y()*vector1.x();
}

} // namepsace geomalia
