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

double LineSegment2D::length() const {
  return (point1() - point0()).length();
}

LineSegment2D LineSegment2D::reverse() const {
  return LineSegment2D(point1(), point0());
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

UnitVector2D normalvector(const LineSegment2D& segment) {
  return normalvector(segment.direction());
}

LineSegment2D rotate(const Rotation2D& R, const LineSegment2D& segment) {
  return LineSegment2D(rotate(R, segment.point0()), rotate(R, segment.point1()));
}

} // namespace wigeon
