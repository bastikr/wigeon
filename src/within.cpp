#include "wigeon/within.h"

#include <boost/variant.hpp>

#include "wigeon/distances.h"
#include "wigeon/winding_number.h"


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
  Vector2D point_transformed = 2 * (rotate(rectangle.rotation().inverse(), point) - rectangle.origin());
  return -rectangle.width() < point_transformed.x()
          && point_transformed.x() < rectangle.width()
          && -rectangle.height() < point_transformed.y()
          && point_transformed.y() < rectangle.height();
}

bool within(const Point2D& point, const Circle2D& circle) {
  return distance2(circle.center(), point) < circle.radius()*circle.radius();
}

bool within(const Point2D& point, const Polygon2D& polygon) {
  return winding_number(point, polygon) != 0;
}


namespace {

class within_visitor : public boost::static_visitor<bool> {
  public:
    within_visitor(const Point2D& point) : point(point) {}

    template <typename T>
    bool operator()(const T& object) {
      return within(point, object);
    }

    const Point2D& point;
};

} // anonymous namespace


bool within(const Point2D& point, const ClosedCurve2D& curve) {
  within_visitor visitor(point);
  return curve.apply_visitor(visitor);
}

bool within(const Point2D& point, const ClosedCurves2D& curves) {
  for (auto& curve: curves) {
    if (!within(point, curve))
      return false;
  }
  return true;
}

bool within(const Point2D& point, const Area2D& area) {
  if (!within(point, area.exterior_curves))
    return false;
  for (auto& curve: area.interior_curves) {
    if (within(point, curve))
      return false;
  }
  return true;
}

} // namespace wigeon
