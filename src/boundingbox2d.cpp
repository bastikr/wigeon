#include "wigeon/boundingbox2d.h"

#include <cmath>


namespace wigeon {

BoundingBox2D::BoundingBox2D(const Point2D& origin, double width, double height)
    : origin_(origin), width_(width), height_(height) {}

BoundingBox2D::BoundingBox2D(const Point2D& p00, const Point2D& p11)
    : origin_((p00.x() + p11.x())/2, (p00.y() + p11.y())/2),
      width_(p11.x() - p00.x()), height_(p11.y() - p00.y()) {}

BoundingBox2D::BoundingBox2D(double x0, double y0, double x1, double y1)
    : origin_((x0 + x1)/2, (y0 + y1)/2),
      width_(x1 - x0), height_(y1 - y0) {}


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

BoundingBox2D combine(const BoundingBox2D& bbox0, const BoundingBox2D& bbox1) {
  double xmin = std::min(bbox0.xmin(), bbox1.xmin());
  double ymin = std::min(bbox0.ymin(), bbox1.ymin());
  double xmax = std::max(bbox0.xmax(), bbox1.xmax());
  double ymax = std::max(bbox0.ymax(), bbox1.ymax());
  return BoundingBox2D(xmin, ymin, xmax, ymax);
}

} // namespace wigeon
