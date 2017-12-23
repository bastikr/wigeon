#include "geomalia/circle2d.h"

namespace geomalia {

Circle2D Circle2D::operator+(const Vector2D& vector) const {
  return Circle2D(center() + vector, radius());
}

Circle2D Circle2D::operator-(const Vector2D& vector) const {
  return Circle2D(center() - vector, radius());
}

} // namespace geomalia
