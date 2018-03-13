#pragma once

#include "wigeon/rotations2d.h"
#include "wigeon/vector2d.h"
#include "wigeon/point2d.h"


namespace wigeon {

struct Ray2D {
  Ray2D(const Point2D& point, const Vector2D& direction): point_(point), direction_(direction) {}
  Ray2D(const Point2D& point0, const Point2D& point1) : point_(point0), direction_(point1-point0) {}

  Point2D point() const {return point_;}
  Vector2D direction() const {return direction_;}

  Point2D point_;
  UnitVector2D direction_;
};

Ray2D operator+(const Ray2D&, const Vector2D&);
Ray2D operator+(const Vector2D&, const Ray2D&);

Ray2D operator-(const Ray2D&, const Vector2D&);

UnitVector2D normalvector(const Ray2D&);

Ray2D rotate(const Rotation2D&, const Ray2D&);

} // namespace wigeon
