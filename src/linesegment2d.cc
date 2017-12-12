#include "geometry/linesegment2d.h"

namespace geometry {

Point2D LineSegment2D::getPoint0() const {
    return Point2D(data[0], data[2]);
  }

Point2D LineSegment2D::getPoint1() const {
  return Point2D(data[1], data[3]);
}

} // namespace geometry
