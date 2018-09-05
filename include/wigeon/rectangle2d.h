#pragma once

#include <array>

#include "wigeon/rotations2d.h" 
#include "wigeon/vector2d.h"
#include "wigeon/point2d.h"


namespace wigeon {

struct Rectangle2D {
  Rectangle2D() {}
  Rectangle2D(const Point2D& origin, double width, double height, const Rotation2D& rotation=0);
  Rectangle2D(const Point2D& point00, const Point2D& point11, const Rotation2D& rotation=0);
  Rectangle2D(double x0, double y0, double x1, double y1, const Rotation2D& rotation=0);

  Point2D origin() const;
  void set_origin(const Point2D&);
  void set_origin(double x, double y);

  double width() const;
  void set_width(double);

  double height() const;
  void set_height(double);

  Rotation2D rotation() const;
  void set_rotation(const Rotation2D&);

  double length() const;
  double area() const;

  Point2D point00() const;
  Point2D point01() const;
  Point2D point10() const;
  Point2D point11() const;

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
