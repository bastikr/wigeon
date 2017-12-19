#include "geometry/isinside.h"

#include "geometry/winding_number.h"


namespace geometry {

bool isinside(const Point2D& point, const Rectangle2D& rectangle) {
  return rectangle.xmin() < point.x() && point.x() < rectangle.xmax()
         && rectangle.ymin() < point.y() && point.y() < rectangle.ymax();
}

bool isinside(const Point2D& point, const Polygon2D& polygon) {
  return winding_number(point, polygon) != 0;
}

} // namespace geometry