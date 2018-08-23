#include "wigeon/line2d.h"

namespace wigeon {

void Line2D::set_origin(const Point2D& p) {
  origin_ = p;
}

void Line2D::set_origin(double x, double y) {
  origin_.set_x(x);
  origin_.set_y(y);
}

void Line2D::set_direction(const UnitVector2D& direction) {
  direction_ = direction;
}

void Line2D::set_direction(double x, double y) {
  direction_.set_x(x);
  direction_.set_y(y);
}

Line2D Line2D::reverse() const {
  return Line2D(origin(), -direction());
}

Line2D operator+(const Line2D& line, const Vector2D& vector) {
  return Line2D(line.origin() + vector, line.direction());
}

Line2D operator+(const Vector2D& vector, const Line2D& line) {
  return Line2D(vector + line.origin(), line.direction());
}

Line2D operator-(const Line2D& line, const Vector2D& vector) {
  return Line2D(line.origin() - vector, line.direction());
}

UnitVector2D normalvector(const Line2D& line) {
  return normalvector(line.direction());
}

Line2D rotate(const Rotation2D& R, const Line2D& line) {
  return Line2D(rotate(R, line.origin()), rotate(R, line.direction()));
}

} // namespace wigeon
