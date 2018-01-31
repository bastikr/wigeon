#include "wigeon/polygon2d_simplification.h"

#include <list>
#include <vector>

#include "wigeon/point2d.h"
#include "wigeon/distances.h"


namespace wigeon {

using PointList = std::list<Point2D>;


namespace {

template <typename PointIter>
PointList douglas_peucker(const PointIter& it_first, const PointIter& it_last, double eps) {
  PointList points;
  if (it_first==it_last)
    return points;

  double d2_max = 0;
  PointIter it_max;
  LineSegment2D segment(*it_first, *it_last);

  PointIter it = it_first;
  while(it!=it_last) {
    double d2 = distance2(segment, *it);
    if (d2 > d2_max) {
      d2_max = d2;
      it_max = it;
    }
    ++it;
  }

  if (d2_max<eps*eps)
    return points;

  points.splice(points.end(), douglas_peucker(it_first, it_max, eps));
  points.push_back(*it_max);
  points.splice(points.end(), douglas_peucker(it_max, it_last, eps));
  return points;
}

} // anonymous namespace


PolyLine2D douglas_peucker(const PolyLine2D& polyline, double eps) {
  size_t size = polyline.size();
  if (size<=2)
    return polyline;
  PointList points = douglas_peucker(polyline.points.begin(), --polyline.points.end(), eps);
  PolyLine2D result;
  result.push_back(polyline.points.front());
  for (auto& p: points)
    result.push_back(p);
  result.push_back(polyline.points.back());
  return result;
}

Polygon2D douglas_peucker(const Polygon2D& polygon, double eps) {
  // Handle special cases
  size_t size = polygon.size();
  if (size==0)
    return polygon;

  // Copy points into list
  PointList points;
  for (size_t i=0; i<size; ++i) {
    points.push_back(polygon.point(i));
  }
  points.push_back(polygon.point(0));

  PointList points_included = douglas_peucker(points.begin(), --points.end(), eps);
  Polygon2D result;
  result.push_back(polygon.point(0));
  for (auto it=points_included.begin(); it!=points_included.end(); ++it) {
    result.push_back(*it);
  }
  return result;
}


} // namespace wigeon
