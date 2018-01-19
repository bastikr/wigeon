#pragma once

#include <array>

#include "wigeon/rotations2d.h"
#include "wigeon/vector2d.h"
#include "wigeon/point2d.h"
#include "wigeon/linesegment2d.h"


namespace wigeon {

struct DoubleLineSegment2D {
  DoubleLineSegment2D(const Point2D& p0, const Point2D& p1, const Point2D& p2)
      : data({{p0.x(), p0.y(), p1.x(), p1.y(), p2.x(), p2.y()}}) {}

  DoubleLineSegment2D(double x0, double y0, double x1, double y1, double x2, double y2)
      : data({{x0, y0, x1, y1, x2, y2}}) {}

  double x0() const {return data[0];}
  double y0() const {return data[1];}
  double x1() const {return data[2];}
  double y1() const {return data[3];}
  double x2() const {return data[4];}
  double y2() const {return data[5];}

  Point2D point0() const {return Point2D(data[0], data[1]);}
  Point2D point1() const {return Point2D(data[2], data[3]);}
  Point2D point2() const {return Point2D(data[4], data[5]);}

  LineSegment2D segment0() const {return LineSegment2D(point0(), point1());}
  LineSegment2D segment1() const {return LineSegment2D(point1(), point2());}

  std::array<double, 6> data;
};

DoubleLineSegment2D operator+(const DoubleLineSegment2D& segment, const Vector2D& vector);
DoubleLineSegment2D operator+(const Vector2D& vector, const DoubleLineSegment2D& segment);

DoubleLineSegment2D operator-(const DoubleLineSegment2D& segment, const Vector2D& vector);
DoubleLineSegment2D operator-(const Vector2D& vector, const DoubleLineSegment2D& segment);

DoubleLineSegment2D rotate(const Rotation2D&, const DoubleLineSegment2D&);

} // namespace wigeon
