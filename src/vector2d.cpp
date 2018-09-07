#include "wigeon/vector2d.h"
#include "wigeon/point2d.h"

#include <cmath>

namespace wigeon {

Vector2D::Vector2D() {}

Vector2D::Vector2D(const Point2D& p)
    : data(p.data) {}

Vector2D::Vector2D(double x, double y)
    : data({{x, y}}) {}

double Vector2D::x() const {
  return data[0];
}

void Vector2D::set_x(double x) {
  data[0] = x;
}

double Vector2D::y() const {
  return data[1];
}

void Vector2D::set_y(double y) {
  data[1] = y;
}

double Vector2D::length2() const {
  return x()*x() + y()*y();
}

double Vector2D::length() const {
  return sqrt(length2());
}

Vector2D Vector2D::reverse() const {
  return -(*this);
}

UnitVector2D::UnitVector2D() {}

UnitVector2D::UnitVector2D(const Vector2D& v)
    : Vector2D(v/v.length()) {}

UnitVector2D::UnitVector2D(double x, double y)
    : UnitVector2D(Vector2D(x, y)) {}

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

UnitVector2D normalvector(const UnitVector2D& v) {
  return UnitVector2D(v.y(), -v.x());
}

UnitVector2D normalvector(const Vector2D& vector) {
  return normalvector(UnitVector2D(vector));
}


Vector2D rotate(const Rotation2D& R, const Vector2D& v) {
  return Vector2D(R.x()*v.x() - R.y()*v.y(), R.y()*v.x() + R.x()*v.y());
}

UnitVector2D rotate(const Rotation2D& R, const UnitVector2D& v) {
  return UnitVector2D(R.x()*v.x() - R.y()*v.y(), R.y()*v.x() + R.x()*v.y());
}


double cross(const Vector2D& vector0, const Vector2D& vector1) {
  return vector0.x()*vector1.y() - vector0.y()*vector1.x();
}

} // namespace wigeon
