#include "wigeon/circle2d.h"

namespace wigeon {

Circle2D operator+(const Circle2D& circle, const Vector2D& vector) {
  return Circle2D(circle.center() + vector, circle.radius());
}

Circle2D operator+(const Vector2D& vector, const Circle2D& circle) {
  return Circle2D(vector + circle.center(), circle.radius());
}

Circle2D operator-(const Circle2D& circle, const Vector2D& vector) {
  return Circle2D(circle.center() - vector, circle.radius());
}

Circle2D operator-(const Vector2D& vector, const Circle2D& circle) {
  return Circle2D(vector - circle.center(), circle.radius());
}

Circle2D rotate(const Rotation2D& R, const Circle2D& circle) {
  return Circle2D(rotate(R, circle.center()), circle.radius());
}

} // namespace wigeon
