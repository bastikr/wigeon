#pragma once

#include <array>

#include "wigeon/rotations2d.h"
#include "wigeon/vector2d.h"
#include "wigeon/point2d.h"


namespace wigeon {

struct LineSegment2D {
  LineSegment2D() {}

  LineSegment2D(const Point2D& p0, const Point2D& p1)
      : data({{p0.x(), p1.x(), p0.y(), p1.y()}}) {}

  LineSegment2D(double x0, double y0, double x1, double y1)
      : data({{x0, x1, y0, y1}}) {}

  double x0() const {return data[0];}
  void set_x0(double x) {data[0] = x;}

  double y0() const {return data[2];}
  void set_y0(double y) {data[2] = y;}

  double x1() const {return data[1];}
  void set_x1(double x) {data[1] = x;}

  double y1() const {return data[3];}
  void set_y1(double y) {data[3] = y;}

  Point2D point0() const;
  void set_point0(const Point2D&);
  void set_point0(double x, double y);

  Point2D point1() const;
  void set_point1(const Point2D&);
  void set_point1(double x, double y);

  UnitVector2D direction() const;

  double length() const;

  LineSegment2D reverse() const;

  std::array<double, 4> data;
};

LineSegment2D operator+(const LineSegment2D&, const Vector2D&);
LineSegment2D operator+(const Vector2D&, const LineSegment2D&);

LineSegment2D operator-(const LineSegment2D&, const Vector2D&);

UnitVector2D normalvector(const LineSegment2D&);

LineSegment2D rotate(const Rotation2D&, const LineSegment2D&);

} // namespace wigeon
