#include "wigeon/point2d.h"


namespace wigeon {

Point2D operator+(const Point2D& point, const Vector2D& vector) {
  return Point2D(point.x() + vector.x(), point.y() + vector.y());
}

Point2D operator+(const Vector2D& vector, const Point2D& point) {
  return Point2D(vector.x() + point.x(), vector.y() + point.y());
}

Point2D operator-(const Point2D& point, const Vector2D& vector) {
  return Point2D(point.x() - vector.x(), point.y() - vector.y());
}

Vector2D operator-(const Point2D& point0, const Point2D& point1) {
  return Vector2D(point0.x() - point1.x(), point0.y()-point1.y());
}


Point2D rotate(const Rotation2D& R, const Point2D& p) {
  return Point2D(R.x()*p.x() - R.y()*p.y(), R.y()*p.x() + R.x()*p.y());
}

} // namespace wigeon
