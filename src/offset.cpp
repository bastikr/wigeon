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

Rectangle2D offset(const Rectangle2D& r, double d) {
  double xmin = r.xmin() - d;
  double xmax = r.xmax() + d;
  double ymin = r.ymin() - d;
  double ymax = r.ymax() + d;
  if (xmin>xmax)
    xmin = xmax = (xmin + xmax)/2;
  if (ymin>ymax)
    ymin = ymax = (ymin + ymax)/2;
  return Rectangle2D(xmin, ymin, xmax, ymax);
}

Polygon2D offset(const Polygon2D& polygon, double d) {
  Polygon2D p_new;
  Line2D line0 = offset(Line2D(*polygon.edge(polygon.size()-1)), d);
  Line2D line1 = line0;
  Points2D points;
  for (int i=0; i<polygon.size(); ++i) {
    line0 = line1;
    line1 = offset(Line2D(*polygon.edge(i)), d);
    points = intersections(line0, line1);
    p_new.push_back(points[0]);
  }
  return p_new;
}

} // namespace wigeon
