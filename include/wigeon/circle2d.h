#pragma once

#include "wigeon/rotations2d.h"
#include "wigeon/vector2d.h"
#include "wigeon/point2d.h"


namespace wigeon {

struct Circle2D {
  Circle2D() {}
  Circle2D(Point2D origin, double radius) : origin_(origin), radius_(radius) {}

  Point2D origin() const {return origin_;}
  void set_origin(const Point2D&);
  void set_origin(double x, double y);

  double& radius() {return radius_;}
  double radius() const {return radius_;}

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
