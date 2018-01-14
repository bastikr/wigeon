#pragma once

#include "wigeon/rotations2d.h"
#include "wigeon/vector2d.h"
#include "wigeon/point2d.h"


namespace wigeon {

struct Circle2D {
  Circle2D(Point2D center, double radius) : center_(center), radius_(radius) {}

  Point2D center() const {return center_;}
  double radius() const {return radius_;}

  Point2D center_;
  double radius_;
};

Circle2D operator+(const Circle2D& circle, const Vector2D& vector);
Circle2D operator+(const Vector2D& vector, const Circle2D& circle);

Circle2D operator-(const Circle2D& circle, const Vector2D& vector);
Circle2D operator-(const Vector2D& vector, const Circle2D& circle);

Circle2D rotate(const Rotation2D&, const Circle2D&);

} // namespace wigeon
