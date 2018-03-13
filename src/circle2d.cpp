#include "wigeon/circle2d.h"

#include <cmath>


namespace wigeon {

double Circle2D::length() const {
  return 2*radius()*M_PI;
}

double Circle2D::length2() const {
  return pow(length(), 2);
}

Circle2D operator+(const Circle2D& circle, const Vector2D& vector) {
  return Circle2D(circle.origin() + vector, circle.radius());
}

Circle2D operator+(const Vector2D& vector, const Circle2D& circle) {
  return Circle2D(vector + circle.origin(), circle.radius());
}

Circle2D operator-(const Circle2D& circle, const Vector2D& vector) {
  return Circle2D(circle.origin() - vector, circle.radius());
}


Circle2D rotate(const Rotation2D& R, const Circle2D& circle) {
  return Circle2D(rotate(R, circle.origin()), circle.radius());
}

} // namespace wigeon
