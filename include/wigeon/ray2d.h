#pragma once

#include "wigeon/rotations2d.h"
#include "wigeon/vector2d.h"
#include "wigeon/point2d.h"


namespace wigeon {

struct Ray2D {
  Ray2D(const Point2D& origin, const Vector2D& direction): origin_(origin), direction_(direction) {}
  Ray2D(const Point2D& origin0, const Point2D& origin1) : origin_(origin0), direction_(origin1-origin0) {}

  Point2D origin() const {return origin_;}
  UnitVector2D direction() const {return direction_;}

  Point2D origin_;
  UnitVector2D direction_;
};

Ray2D operator+(const Ray2D&, const Vector2D&);
Ray2D operator+(const Vector2D&, const Ray2D&);

Ray2D operator-(const Ray2D&, const Vector2D&);

UnitVector2D normalvector(const Ray2D&);

Ray2D rotate(const Rotation2D&, const Ray2D&);

} // namespace wigeon
