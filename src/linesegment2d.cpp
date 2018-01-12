#include "wigeon/linesegment2d.h"

#include <cmath>


namespace wigeon {

Point2D LineSegment2D::point0() const {
    return Point2D(data[0], data[2]);
  }

Point2D LineSegment2D::point1() const {
  return Point2D(data[1], data[3]);
}

UnitVector2D LineSegment2D::direction() const {
  return UnitVector2D(point1() - point0());
}

double LineSegment2D::length2() const {
  double dx = x1() - x0();
  double dy = y1() - y0();
  return dx*dx + dy*dy;
}

double LineSegment2D::length() const {
  return sqrt(length2());
}

LineSegment2D operator+(const LineSegment2D& segment, const Vector2D& vector) {
  return LineSegment2D(segment.point0() + vector, segment.point1() + vector);
}

LineSegment2D operator+(const Vector2D& vector, const LineSegment2D& segment)  {
  return LineSegment2D(vector + segment.point0(), vector + segment.point1());
}

LineSegment2D operator-(const LineSegment2D& segment, const Vector2D& vector) {
  return LineSegment2D(segment.point0() - vector, segment.point1() - vector);
}

LineSegment2D operator-(const Vector2D& vector, const LineSegment2D& segment) {
  return LineSegment2D(vector - segment.point0(), vector - segment.point1());
}

UnitVector2D normalvector(const LineSegment2D& segment) {
  return normalvector(segment.direction());
}

} // namespace wigeon
