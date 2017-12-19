#include "geomalia/ray2d.h"

namespace geomalia {

Ray2D Ray2D::operator+(const Vector2D& vector) const {
  return Ray2D(point + vector, direction);
}

Ray2D Ray2D::operator-(const Vector2D& vector) const {
  return Ray2D(point - vector, direction);
}

} // namespace geomalia
