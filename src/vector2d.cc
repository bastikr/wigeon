#include "wigeon/vector2d.h"

#include <cmath>

namespace wigeon {

double Vector2D::length2() const {
  return x()*x() + y()*y();
}

double Vector2D::length() const {
  return sqrt(length2());
}

Vector2D operator+(const Vector2D& vector0, const Vector2D& vector1) {
  return Vector2D(vector0.x() + vector1.x(), vector0.y() + vector1.y());
}


Vector2D operator-(const Vector2D& vector) {
  return Vector2D(-vector.x(), -vector.y());
}

Vector2D operator-(const Vector2D& vector0, const Vector2D& vector1) {
  return Vector2D(vector0.x() - vector1.x(), vector0.y() - vector1.y());
}


Vector2D operator*(const Vector2D& vector, double a) {
  return Vector2D(vector.x()*a, vector.y()*a);
}

Vector2D operator*(double a, const Vector2D& vector) {
  return Vector2D(a*vector.x(), a*vector.y());
}

double operator*(const Vector2D& vector0, const Vector2D& vector1) {
  return vector0.x()*vector1.x() + vector0.y()*vector1.y();
}


Vector2D operator/(const Vector2D& vector, double a) {
  return Vector2D(vector.x()/a, vector.y()/a);
}

double cross(const Vector2D& vector0, const Vector2D& vector1) {
  return vector0.x()*vector1.y() - vector0.y()*vector1.x();
}

} // namepsace wigeon
