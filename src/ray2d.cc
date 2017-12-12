#include "geometry/ray2d.h"

namespace geometry {

Ray2D Ray2D::operator+(const Vector2D& vector) const {
  return Ray2D(point + vector, direction);
}

Ray2D Ray2D::operator-(const Vector2D& vector) const {
  return Ray2D(point - vector, direction);
}

} // namespace geometry
