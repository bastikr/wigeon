#pragma once

#include <vector>
#include <boost/optional.hpp>

#include "geomalia/vector2d.h"
#include "geomalia/point2d.h"
#include "geomalia/linesegment2d.h"
#include "geomalia/rectangle2d.h"


namespace geomalia {

struct Polygon2D {
  void append(const Point2D& point);
  void append(double x, double y);
  void append(const LineSegment2D& segment);

  int size() const;

  boost::optional<Rectangle2D> bounding_box() const;

  boost::optional<Point2D> point(int i) const;
  boost::optional<LineSegment2D> edge(int i) const;

  std::vector<double> data_x;
  std::vector<double> data_y;
};

Polygon2D operator+(Polygon2D polygon, const Vector2D& v);
Polygon2D operator-(Polygon2D polygon, const Vector2D& v);

} // namespace geomalia
