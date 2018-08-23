#pragma once

#include <array>

#include "wigeon/rotations2d.h"
#include "wigeon/vector2d.h"
#include "wigeon/point2d.h"
#include "wigeon/linesegment2d.h"


namespace wigeon {

struct Line2D {
  Line2D() {}
  Line2D(const Point2D& point, const Vector2D& direction) : origin_(point), direction_(direction) {}
  Line2D(const Point2D& point0, const Point2D& point1) : origin_(point0), direction_(point1-point0) {}
  explicit Line2D(const LineSegment2D& segment) : origin_(segment.point0()), direction_(segment.direction()) {}

  Point2D origin() const {return origin_;}
  void set_origin(const Point2D&);
  void set_origin(double, double);

  UnitVector2D direction() const {return direction_;}
  void set_direction(const UnitVector2D&);
  void set_direction(double x, double y);

  Line2D reverse() const;

  Point2D origin_;
  UnitVector2D direction_;
};

Line2D operator+(const Line2D&, const Vector2D&);
Line2D operator+(const Vector2D&, const Line2D&);

Line2D operator-(const Line2D&, const Vector2D&);

UnitVector2D normalvector(const Line2D&);

Line2D rotate(const Rotation2D&, const Line2D&);

} // namespace wigeon
