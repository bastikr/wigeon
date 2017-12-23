#include "geomalia/line2d.h"

namespace geomalia {

Line2D operator+(const Line2D& line, const Vector2D& vector) {
  return Line2D(line.getPoint() + vector, line.getDirection());
}

Line2D operator+(const Vector2D& vector, const Line2D& line) {
  return Line2D(vector + line.getPoint(), line.getDirection());
}

Line2D operator-(const Line2D& line, const Vector2D& vector) {
  return Line2D(line.getPoint() - vector, line.getDirection());
}

Line2D operator-(const Vector2D& vector, const Line2D& line) {
  return Line2D(vector - line.getPoint(), line.getDirection());
}

} // namespace geomalia
