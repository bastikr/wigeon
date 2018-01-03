#include "wigeon/intersections.h"

#include <cmath>


namespace wigeon {

Points2D intersections(const Line2D& line0, const Line2D& line1) {
  const Point2D& p0 = line0.point();
  const Point2D& p1 = line1.point();
  const Vector2D& w0 = line0.direction();
  const Vector2D& w1 = line1.direction();
  double a = w0*w1;
  Points2D points;
  if (1-a*a < 1e-15)
    return Points2D();
  double c0 = (p1-p0) * (w0 - w1*(w0*w1)) / (1-a*a);
  points.push_back(p0 + w0*c0);
  return points;
}

} // namespace wigeon
