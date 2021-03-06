#pragma once

#include <array>

#include "wigeon/vector2d.h"
#include "wigeon/point2d.h"
#include "wigeon/linesegment2d.h"
#include "wigeon/triangle2d.h"
#include "wigeon/rectangle2d.h"
#include "wigeon/circle2d.h"
#include "wigeon/polygon2d.h"
#include "wigeon/polyline2d.h"
#include "wigeon/concepts2d.h"
#include "wigeon/area2d.h"


namespace wigeon {

struct BoundingBox2D {
  BoundingBox2D();
  BoundingBox2D(const Point2D& origin, double width, double height);
  BoundingBox2D(const Point2D& point00, const Point2D& point11);
  BoundingBox2D(double x0, double y0, double x1, double y1);

  Point2D origin() const;
  void set_origin(const Point2D&);
  void set_origin(double x, double y);

  double width() const;
  void set_width(double);

  double height() const;
  void set_height(double);

  double area() const;

  bool isnan() const;

  double xmin() const;
  double xmax() const;
  double ymin() const;
  double ymax() const;

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
BoundingBox2D boundingbox(const Rectangle2D&);
BoundingBox2D boundingbox(const Circle2D&);
BoundingBox2D boundingbox(const Polygon2D&);
BoundingBox2D boundingbox(const PolyLine2D&);
BoundingBox2D boundingbox(const FiniteCurve2D&);
BoundingBox2D boundingbox(const Area2D&);

} // namespace wigeon
