#pragma once

#include <array>

#include "wigeon/vector2d.h"
#include "wigeon/point2d.h"


namespace wigeon {

struct LineSegment2D {
  LineSegment2D(const LineSegment2D& segment)
      : data(segment.data) {}

  LineSegment2D(const Point2D& p0, const Point2D& p1)
      : data({{p0.x(), p1.x(), p0.y(), p1.y()}}) {}

  LineSegment2D(double x0, double y0, double x1, double y1)
      : data({{x0, x1, y0, y1}}) {}

  double x0() const {return data[0];}
  double y0() const {return data[1];}
  double x1() const {return data[2];}
  double y1() const {return data[3];}

  Point2D point0() const;
  Point2D point1() const;

  std::array<double, 4> data;
};

LineSegment2D operator+(const LineSegment2D& segment, const Vector2D& vector);
LineSegment2D operator+(const Vector2D& vector, const LineSegment2D& segment);

LineSegment2D operator-(const LineSegment2D& segment, const Vector2D& vector);
LineSegment2D operator-(const Vector2D& vector, const LineSegment2D& segment);

} // namespace wigeon
