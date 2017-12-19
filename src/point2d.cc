#include "geomalia/point2d.h"
#include "geomalia/vector2d.h"

namespace geomalia {

Point2D Point2D::operator+(const Vector2D& vector) const {
  return Point2D(vector.x() + x(), vector.y() + y());
}

Vector2D Point2D::operator-(const Point2D& point) const {
  return Vector2D(x()-point.x(), y()-point.y());
}

Point2D Point2D::operator-(const Vector2D& vector) const {
  return Point2D(x()-vector.x(), y()-vector.y());
}

} // namespace geomalia
