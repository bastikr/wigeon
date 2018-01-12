#include "wigeon/line2d.h"

namespace wigeon {

Line2D operator+(const Line2D& line, const Vector2D& vector) {
  return Line2D(line.point() + vector, line.direction());
}

Line2D operator+(const Vector2D& vector, const Line2D& line) {
  return Line2D(vector + line.point(), line.direction());
}

Line2D operator-(const Line2D& line, const Vector2D& vector) {
  return Line2D(line.point() - vector, line.direction());
}

Line2D operator-(const Vector2D& vector, const Line2D& line) {
  return Line2D(vector - line.point(), line.direction());
}

UnitVector2D normalvector(const Line2D& line) {
  return normalvector(line.direction());
}

} // namespace wigeon
