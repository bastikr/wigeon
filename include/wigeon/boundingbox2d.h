#pragma once

#include <array>

#include "wigeon/vector2d.h"
#include "wigeon/point2d.h"
#include "wigeon/linesegment2d.h"
#include "wigeon/triangle2d.h"
#include "wigeon/rectangle2d.h"
#include "wigeon/circle2d.h"


namespace wigeon {

struct BoundingBox2D {
  BoundingBox2D(const Point2D& origin, double width, double height);
  BoundingBox2D(const Point2D& point00, const Point2D& point11);
  BoundingBox2D(double x0, double y0, double x1, double y1);

  Point2D origin() const {return origin_;}
  double width() const {return width_;}
  double height() const {return height_;}
  double area() const {return width_*height_;}

  double xmin() const {return origin_.x() - 0.5*width_;}
  double xmax() const {return origin_.x() + 0.5*width_;}
  double ymin() const {return origin_.y() - 0.5*height_;}
  double ymax() const {return origin_.y() + 0.5*height_;}

  Point2D origin_;
  double width_;
  double height_;
};

BoundingBox2D operator+(const BoundingBox2D&, const Vector2D&);
BoundingBox2D operator+(const Vector2D&, const BoundingBox2D&);

BoundingBox2D operator-(const BoundingBox2D&, const Vector2D&);


bool overlap(const BoundingBox2D&, const BoundingBox2D&);
BoundingBox2D combine(const BoundingBox2D&, const BoundingBox2D&);


BoundingBox2D boundingbox(const LineSegment2D&);
BoundingBox2D boundingbox(const Triangle2D&);
BoundingBox2D boundingbox(const Circle2D&);

} // namespace wigeon
