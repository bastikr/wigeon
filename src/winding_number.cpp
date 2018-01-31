#include "wigeon/winding_number.h"


namespace wigeon {

namespace {

int delta_winding_number(const Point2D& point, const Point2D& p0, const Point2D& p1) {
  if (p0.y()<=point.y()) {
    if (p1.y()>point.y() && cross(p1-p0, point-p0)>0)
      return 1;
  } else {
    if (p1.y()<=point.y() && cross(p1-p0, point-p0)<0)
      return -1;
  }
  return 0;
}

} // namespace

int winding_number(const Point2D& point, const Polygon2D& polygon) {
  int n = 0;
  size_t size = polygon.size();
  for (size_t i=0; i<size-1; ++i) {
    n += delta_winding_number(point, polygon.point(i), polygon.point(i+1));
  }
  return n + delta_winding_number(point, polygon.point(size-1), polygon.point(0));
}

} // namespace wigeon
