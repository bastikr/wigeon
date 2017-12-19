#include "geomalia/isinside.h"

#include "geomalia/distances.h"
#include "geomalia/winding_number.h"


namespace geomalia {

bool isinside(const Point2D& point, const Rectangle2D& rectangle) {
  return rectangle.xmin() < point.x() && point.x() < rectangle.xmax()
         && rectangle.ymin() < point.y() && point.y() < rectangle.ymax();
}

bool isinside(const Point2D& point, const Circle2D& circle) {
  return distance2(circle.center, point) < circle.radius*circle.radius;
}

bool isinside(const Point2D& point, const Polygon2D& polygon) {
  return winding_number(point, polygon) != 0;
}

} // namespace geomalia