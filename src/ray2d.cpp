#include "wigeon/ray2d.h"


namespace wigeon {

Ray2D::Ray2D(const Point2D& origin, const Vector2D& direction)
    : origin_(origin), direction_(direction) {}

Ray2D::Ray2D(const Point2D& origin0, const Point2D& origin1)
    : origin_(origin0), direction_(origin1-origin0) {}

Point2D Ray2D::origin() const {
  return origin_;
}

void Ray2D::set_origin(const Point2D& point) {
  origin_ = point;
}

void Ray2D::set_origin(double x, double y) {
  origin_.set_x(x);
  origin_.set_y(y);
}

UnitVector2D Ray2D::direction() const {
  return direction_;
}

void Ray2D::set_direction(const Vector2D& vector) {
  direction_ = vector;
}

void Ray2D::set_direction(double x, double y) {
  direction_ = UnitVector2D(x, y);
}

Ray2D operator+(const Ray2D& ray, const Vector2D& vector) {
  return Ray2D(ray.origin() + vector, ray.direction());
}

Ray2D operator+(const Vector2D& vector, const Ray2D& ray) {
  return Ray2D(vector + ray.origin(), ray.direction());
}

Ray2D operator-(const Ray2D& ray, const Vector2D& vector) {
  return Ray2D(ray.origin() - vector, ray.direction());
}

UnitVector2D normalvector(const Ray2D& ray) {
  return normalvector(ray.direction());
}

Ray2D rotate(const Rotation2D& R, const Ray2D& ray) {
  return Ray2D(rotate(R, ray.origin()), rotate(R, ray.direction()));
}

} // namespace wigeon
