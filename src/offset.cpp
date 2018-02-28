#include "wigeon/offset.h"

#include "wigeon/intersections.h"


namespace wigeon {

Line2D offset(const Line2D& line, double d) {
  return line + d*normalvector(line);
}

Ray2D offset(const Ray2D& ray, double d){
  return ray + d*normalvector(ray);
}

LineSegment2D offset(const LineSegment2D& segment, double d) {
  return segment + d*normalvector(segment);
}

Circle2D offset(const Circle2D& circle, double d) {
  double radius = circle.radius() + d;
  if (radius>0)
    return Circle2D(circle.center(), radius);
  return Circle2D(circle.center(), 0);
}

Rectangle2D offset(const Rectangle2D& rectangle, double d) {
  double width = rectangle.width() + 2*d;
  if (width < 0)
    width = 0;
  double height = rectangle.height() + 2*d;
  if (height < 0)
    height = 0;
  return Rectangle2D(rectangle.origin(), width, height, rectangle.rotation());
}

Polygon2D offset(const Polygon2D& polygon, double d) {
  Polygon2D p_new;
  Line2D line0 = offset(Line2D(polygon.edge(polygon.size()-1)), d);
  Line2D line1 = line0;
  Points2D points;
  for (size_t i=0; i<polygon.size(); ++i) {
    line0 = line1;
    line1 = offset(Line2D(polygon.edge(i)), d);
    points = intersections(line0, line1);
    p_new.push_back(points[0]);
  }
  return p_new;
}


namespace {

template <typename T1>
class offset_visitor : public boost::static_visitor<T1> {
  public:
    offset_visitor(double d) : d(d) {}

    template <typename T>
    T1 operator()(const T& object) {
      return offset(object, d);
    }

    double d;
};

} // anonymous namespace


ClosedCurve2D offset(const ClosedCurve2D& curve, double d) {
  offset_visitor<ClosedCurve2D> visitor(d);
  return curve.apply_visitor(visitor);
}

Area2D offset(const Area2D& area, double d) {
  Area2D area_new;
  for (const auto& curve: area.exterior_curves) {
    area_new.exterior_curves.push_back(offset(curve, d));
  }
  for (const auto& curve: area.interior_curves) {
    area_new.interior_curves.push_back(offset(curve, -d));
  }
  return area_new;
}

} // namespace wigeon
