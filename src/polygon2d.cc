# include "geomalia/polygon2d.h"

#include <algorithm>


namespace geomalia {

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

Polygon2D operator+(Polygon2D polygon, const Vector2D& v) {
  for (int i=0; i<polygon.size(); ++i) {
    polygon.data_x[i] += v.x();
    polygon.data_y[i] += v.y();
  }
  return polygon;
}

Polygon2D operator-(Polygon2D polygon, const Vector2D& v) {
  for (int i=0; i<polygon.size(); ++i) {
    polygon.data_x[i] -= v.x();
    polygon.data_y[i] -= v.y();
  }
  return polygon;
}

boost::optional<Rectangle2D> Polygon2D::bounding_box() const {
  if (size()==0)
    return boost::optional<Rectangle2D>();
  double xmin = data_x[0];
  double xmax = data_x[0];
  double ymin = data_y[0];
  double ymax = data_y[0];
  for (int i=1; i<size(); ++i) {
    xmin = std::min(xmin, data_x[i]);
    xmax = std::max(xmax, data_x[i]);
    ymin = std::min(ymin, data_y[i]);
    ymax = std::max(ymax, data_y[i]);
  }
  return Rectangle2D(xmin, ymin, xmax, ymax);
}

boost::optional<Point2D> Polygon2D::point(int i) const {
  if (i<0 || i>=size())
    return boost::optional<Point2D>();
  else
    return Point2D(data_x[i], data_y[i]);
}

boost::optional<LineSegment2D> Polygon2D::edge(int i) const {
  if (i<0 || i>size()-1)
    return boost::optional<LineSegment2D>();
  if (i==size())
    return LineSegment2D(data_x[i], data_y[i], data_x[0], data_y[0]);
  return LineSegment2D(data_x[i], data_y[i], data_x[i+1], data_y[i+1]);
}

} // namespace geomalia
