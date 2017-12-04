#include "geometry/geometry.h"

namespace geometry {

Point2D Vector2D::operator+(Point2D point) {
  point.data[0] += data[0];
  point.data[1] += data[1];
  return point;
}

Point2D Vector2D::operator-(Point2D point) {
  point.data[0] -= data[0];
  point.data[1] -= data[1];
  return point;
}

Vector2D Vector2D::operator+(Vector2D vector) {
  vector.data[0] += data[0];
  vector.data[1] += data[1];
  return vector;
}

} // namepsace geometry
