#include "wigeon/linesegment2d.h"

#include <cmath>


namespace wigeon {

LineSegment2D::LineSegment2D(const Point2D& p0, const Point2D& p1)
    : data({{p0.x(), p1.x(), p0.y(), p1.y()}}) {}

LineSegment2D::LineSegment2D(double x0, double y0, double x1, double y1)
    : data({{x0, x1, y0, y1}}) {}

double LineSegment2D::x0() const {
  return data[0];
}

void LineSegment2D::set_x0(double x) {
  data[0] = x;
}

double LineSegment2D::y0() const {
  return data[2];
}

void LineSegment2D::set_y0(double y) {
  data[2] = y;
}

double LineSegment2D::x1() const {
  return data[1];
}

void LineSegment2D::set_x1(double x) {
  data[1] = x;
}

double LineSegment2D::y1() const {
  return data[3];
}

void LineSegment2D::set_y1(double y) {
  data[3] = y;
}

Point2D LineSegment2D::point0() const {
  return Point2D(data[0], data[2]);
}

void LineSegment2D::set_point0(const Point2D& p) {
  data[0] = p.x();
  data[2] = p.y();
}

void LineSegment2D::set_point0(double x, double y) {
  data[0] = x;
  data[2] = y;
}

Point2D LineSegment2D::point1() const {
  return Point2D(data[1], data[3]);
}

void LineSegment2D::set_point1(const Point2D& p) {
  data[1] = p.x();
  data[3] = p.y();
}

void LineSegment2D::set_point1(double x, double y) {
  data[1] = x;
  data[3] = y;
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
