#pragma once

#include <array>

#include "wigeon/rotations2d.h"
#include "wigeon/vector2d.h"
#include "wigeon/point2d.h"
#include "wigeon/linesegment2d.h"


namespace wigeon {

struct Line2D {
  Line2D(Point2D point, Vector2D direction) : point_(point), direction_(direction) {}
  Line2D(Point2D point0, Point2D point1) : point_(point0), direction_(point1-point0) {}
  explicit Line2D(LineSegment2D segment) : point_(segment.point0()), direction_(segment.direction()) {}

  Point2D point() const {return point_;}
  Vector2D direction() const {return direction_;}

  Point2D point_;
  UnitVector2D direction_;
};

Line2D operator+(const Line2D&, const Vector2D&);
Line2D operator+(const Vector2D&, const Line2D&);

Line2D operator-(const Line2D&, const Vector2D&);
Line2D operator-(const Vector2D&, const Line2D&);

UnitVector2D normalvector(const Line2D&);

Line2D rotate(const Rotation2D&, const Line2D&);

} // namespace wigeon
