#include "wigeon/within.h"

#include "wigeon/distances.h"
#include "wigeon/winding_number.h"

#include "wigeon/printer.h"


namespace wigeon {

bool within(const Point2D& point, const Triangle2D& triangle) {
  Vector2D v0 = triangle.point0() - point;
  Vector2D v1 = triangle.point1() - point;
  Vector2D v2 = triangle.point2() - point;

  double n0 = cross(v0, v1);
  if (n0==0)
    return false;
  double n1 = cross(v1, v2);
  if ((n0>0 && n1<0) || (n0<0 && n1>0))
   return false;
  double n2 = cross(v2, v0);
  return (n0>0 && n2>0) || (n0<0 && n2<0); 
}

bool within(const Point2D& point, const Rectangle2D& rectangle) {
  return rectangle.xmin() < point.x() && point.x() < rectangle.xmax()
         && rectangle.ymin() < point.y() && point.y() < rectangle.ymax();
}

bool within(const Point2D& point, const Circle2D& circle) {
  return distance2(circle.center(), point) < circle.radius()*circle.radius();
}

bool within(const Point2D& point, const Polygon2D& polygon) {
  return winding_number(point, polygon) != 0;
}

} // namespace wigeon