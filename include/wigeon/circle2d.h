#pragma once

#include "wigeon/rotations2d.h"
#include "wigeon/vector2d.h"
#include "wigeon/point2d.h"


namespace wigeon {

struct Circle2D {
  Circle2D() {}
  Circle2D(Point2D origin, double radius);

  Point2D origin() const;
  void set_origin(const Point2D&);
  void set_origin(double x, double y);

  double radius() const;
  void set_radius(double);

  double length() const;
  double area() const;

  Point2D origin_;
  double radius_;
};

Circle2D operator+(const Circle2D&, const Vector2D&);
Circle2D operator+(const Vector2D&, const Circle2D&);

Circle2D operator-(const Circle2D&, const Vector2D&);

Circle2D rotate(const Rotation2D&, const Circle2D&);

} // namespace wigeon
