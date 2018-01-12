#include "wigeon/printer.h"

namespace wigeon {

std::ostream& operator<<(std::ostream& os, const Point1D& point) {
  os << "Point1D(" << point.x() << ")";
  return os;
}

std::ostream& operator<<(std::ostream& os, const Vector1D& vector) {
  os << "Vector1D(" << vector.x() << ")";
  return os;
}


std::ostream& operator<<(std::ostream& os, const Point2D& point) {
  os << "Point2D(" << point.x() << ", " << point.y() << ")";
  return os;
}

std::ostream& operator<<(std::ostream& os, const Vector2D& vector) {
  os << "Vector2D(" << vector.x() << ", " << vector.y() << ")";
  return os;
}

std::ostream& operator<<(std::ostream& os, const Line2D& line) {
  os << "Line2D(" << line.point() << ", " << line.direction() << ")";
  return os;
}

std::ostream& operator<<(std::ostream& os, const Ray2D& ray) {
  os << "Ray2D(" << ray.point() << ", " << ray.direction() << ")";
  return os;
}

std::ostream& operator<<(std::ostream& os, const LineSegment2D& segment) {
  os << "LineSegment2D(" << segment.point0() << ", " << segment.point1() << ")";
  return os;
}

std::ostream& operator<<(std::ostream& os, const Rectangle2D& rectangle) {
  os << "Rectangle2D(" << rectangle.point00() << ", " << rectangle.point11() << ")";
  return os;
}

std::ostream& operator<<(std::ostream& os, const Circle2D& circle) {
  os << "Circle2D(" << circle.center() << ", " << circle.radius() << ")";
  return os;
}


std::ostream& operator<<(std::ostream& os, const Point3D& point) {
  os << "Point3D(" << point.x() << ", " << point.y() << ", " << point.z() << ")";
  return os;
}

std::ostream& operator<<(std::ostream& os, const Vector3D& vector) {
  os << "Vector3D(" << vector.x() << ", " << vector.y() <<  ", " << vector.z() << ")";
  return os;
}

} // namespace wigeon
