#include "wigeon/boundingbox2d.h"

#include <cmath>


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

bool overlap(const BoundingBox2D& box0, const BoundingBox2D& box1) {
  return std::abs(box0.origin().x() - box1.origin().x()) < (box0.width() + box1.width())/2
      && std::abs(box0.origin().y() - box1.origin().y()) < (box0.height() + box1.height())/2;
}

} // namespace wigeon
