#pragma once

#include <vector>
#include <boost/optional.hpp>

#include "geometry/point2d.h"
#include "geometry/linesegment2d.h"
#include "geometry/rectangle2d.h"


namespace geometry {

struct Polygon2D {
  void append(const Point2D& point);
  void append(double x, double y);
  void append(const LineSegment2D& segment);

  int size() const;

  boost::optional<Rectangle2D> bounding_box() const;

  boost::optional<Point2D> getPoint(int i) const;
  boost::optional<LineSegment2D> getLineSegment(int i) const;

  std::vector<double> data_x;
  std::vector<double> data_y;
};

} // namespace geometry
