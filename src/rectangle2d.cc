#include "geometry/rectangle2d.h"


namespace geometry {

Rectangle2D::Rectangle2D(double xmin, double ymin, double xmax, double ymax) {
  data[0] = xmin;
  data[1] = ymin;
  data[2] = xmax;
  data[3] = ymax;
}

Rectangle2D::Rectangle2D(Point2D pmin, Point2D pmax) {
  data[0] = pmin.x();
  data[1] = pmin.y();
  data[2] = pmax.x();
  data[3] = pmax.y();
}

} // namespace geometry
