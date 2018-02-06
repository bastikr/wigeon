#include "wigeon/boundingbox2d.h"


namespace wigeon {

BoundingBox2D::BoundingBox2D(double xmin, double ymin, double xmax, double ymax) {
  data[0] = xmin;
  data[1] = ymin;
  data[2] = xmax;
  data[3] = ymax;
}

BoundingBox2D::BoundingBox2D(Point2D pmin, Point2D pmax) {
  data[0] = pmin.x();
  data[1] = pmin.y();
  data[2] = pmax.x();
  data[3] = pmax.y();
}

BoundingBox2D operator+(const BoundingBox2D& segment, const Vector2D& vector) {
  return BoundingBox2D(segment.point00() + vector, segment.point11() + vector);
}

BoundingBox2D operator+(const Vector2D& vector, const BoundingBox2D& segment)  {
  return BoundingBox2D(vector + segment.point00(), vector + segment.point11());
}

BoundingBox2D operator-(const BoundingBox2D& segment, const Vector2D& vector) {
  return BoundingBox2D(segment.point00() - vector, segment.point11() - vector);
}

BoundingBox2D operator-(const Vector2D& vector, const BoundingBox2D& segment) {
  return BoundingBox2D(vector - segment.point00(), vector - segment.point11());
}


} // namespace wigeon
