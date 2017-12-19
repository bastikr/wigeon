#include "geomalia/line2d.h"

namespace geomalia {

Line2D Line2D::operator+(const Vector2D& vector) const {
  return Line2D(point + vector, direction);
}

} // namespace geomalia
