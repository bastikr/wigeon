# include "geometry/polygon2d.h"

namespace geometry {

void Polygon2D::append(const Point2D& point) {
  data_x.push_back(point.x());
  data_y.push_back(point.y());
}

void Polygon2D::append(double x, double y) {
  data_x.push_back(x);
  data_y.push_back(y);
}

void Polygon2D::append(const LineSegment2D& segment) {
  data_x.push_back(segment.x0());
  data_y.push_back(segment.y0());
  data_x.push_back(segment.x1());
  data_y.push_back(segment.y1());
}

int Polygon2D::size() const {
  return data_x.size();
}

boost::optional<Point2D> Polygon2D::getPoint(int i) const {
  if (i<0 || i>size())
    return boost::optional<Point2D>();
  else
    return Point2D(data_x[i], data_y[i]);
}

boost::optional<LineSegment2D> Polygon2D::getLineSegment(int i) const {
  if (i<0 || i>size()-1)
    return boost::optional<LineSegment2D>();
  if (i==size())
    return LineSegment2D(data_x[i], data_y[i], data_x[0], data_y[0]);
  return LineSegment2D(data_x[i], data_y[i], data_x[i+1], data_y[i+1]);
}

} // namespace geometry
