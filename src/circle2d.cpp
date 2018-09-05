#include "wigeon/circle2d.h"

#include <cmath>


namespace wigeon {

Circle2D::Circle2D(Point2D origin, double radius)
    : origin_(origin), radius_(radius) {}

Point2D Circle2D::origin() const {
  return origin_;
}

void Circle2D::set_radius(double radius) {
  radius_ = radius;
}

double Circle2D::radius() const {
  return radius_;
}

void Circle2D::set_origin(const Point2D& p) {
  origin_ = p;
}

void Circle2D::set_origin(double x, double y) {
  origin_.set_x(x);
  origin_.set_y(y);
}

double Circle2D::length() const {
  return 2*radius()*M_PI;
}

double Circle2D::area() const {
  return pow(radius(), 2) * M_PI;
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
