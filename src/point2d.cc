#include "geometry/geometry.h"

namespace geometry {

Point2D Point2D::operator+(const Vector2D& vector) {
  return Point2D(vector.x() + x(), vector.y() + y());
}

} // namespace geometry
