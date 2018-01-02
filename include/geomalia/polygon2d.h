#pragma once

#include <vector>
#include <boost/optional.hpp>

#include "geomalia/point2d.h"
#include "geomalia/linesegment2d.h"
#include "geomalia/rectangle2d.h"


namespace geomalia {

struct Polygon2D {
  void append(const Point2D& point);
  void append(double x, double y);
  void append(const LineSegment2D& segment);

  int size() const;

  Polygon2D operator+(const Vector2D& v) const;
  Polygon2D operator-(const Vector2D& v) const;

  boost::optional<Rectangle2D> bounding_box() const;

  boost::optional<Point2D> point(int i) const;
  boost::optional<LineSegment2D> edge(int i) const;

  std::vector<double> data_x;
  std::vector<double> data_y;
};

} // namespace geomalia
