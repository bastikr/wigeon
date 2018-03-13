#pragma once

#include <array>

#include "wigeon/rotations2d.h" 
#include "wigeon/vector2d.h"
#include "wigeon/point2d.h"


namespace wigeon {

struct Rectangle2D {
  Rectangle2D(const Point2D& origin, double width, double height, const Rotation2D& rotation=0);
  Rectangle2D(const Point2D& point00, Point2D& point11, const Rotation2D& rotation=0);
  Rectangle2D(double x0, double y0, double x1, double y1, const Rotation2D& rotation=0);

  Point2D origin() const {return origin_;}
  double width() const {return width_;}
  double height() const {return height_;}
  Rotation2D rotation() const {return rotation_;}

  double length() const;
  double length2() const;

  Point2D point00() const {return origin_ + rotate(rotation_, Vector2D(-0.5*width_, -0.5*height_));}
  Point2D point01() const {return origin_ + rotate(rotation_, Vector2D(-0.5*width_, 0.5*height_));}
  Point2D point10() const {return origin_ + rotate(rotation_, Vector2D(0.5*width_, -0.5*height_));}
  Point2D point11() const {return origin_ + rotate(rotation_, Vector2D(0.5*width_, 0.5*height_));}

  Point2D origin_;
  double width_;
  double height_;
  Rotation2D rotation_;
};

Rectangle2D operator+(const Rectangle2D&, const Vector2D&);
Rectangle2D operator+(const Vector2D&, const Rectangle2D&);

Rectangle2D operator-(const Rectangle2D&, const Vector2D&);

Rectangle2D rotate(const Rotation2D&, const Rectangle2D&);

} // namespace wigeon
