#include "wigeon/line2d.h"

namespace wigeon {

Line2D Line2D::reverse() const {
  return Line2D(origin(), -direction());
}

Line2D operator+(const Line2D& line, const Vector2D& vector) {
  return Line2D(line.origin() + vector, line.direction());
}

Line2D operator+(const Vector2D& vector, const Line2D& line) {
  return Line2D(vector + line.origin(), line.direction());
}

Line2D operator-(const Line2D& line, const Vector2D& vector) {
  return Line2D(line.origin() - vector, line.direction());
}

UnitVector2D normalvector(const Line2D& line) {
  return normalvector(line.direction());
}

Line2D rotate(const Rotation2D& R, const Line2D& line) {
  return Line2D(rotate(R, line.origin()), rotate(R, line.direction()));
}

} // namespace wigeon
