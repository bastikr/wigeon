#include "wigeon/rectangle2d.h"


namespace wigeon {

Rectangle2D::Rectangle2D(double xmin, double ymin, double xmax, double ymax) {
  data[0] = xmin;
  data[1] = ymin;
  data[2] = xmax;
  data[3] = ymax;
}

Rectangle2D::Rectangle2D(Point2D pmin, Point2D pmax) {
  data[0] = pmin.x();
  data[1] = pmin.y();
  data[2] = pmax.x();
  data[3] = pmax.y();
}

Rectangle2D operator+(const Rectangle2D& segment, const Vector2D& vector) {
  return Rectangle2D(segment.point00() + vector, segment.point11() + vector);
}

Rectangle2D operator+(const Vector2D& vector, const Rectangle2D& segment)  {
  return Rectangle2D(vector + segment.point00(), vector + segment.point11());
}

Rectangle2D operator-(const Rectangle2D& segment, const Vector2D& vector) {
  return Rectangle2D(segment.point00() - vector, segment.point11() - vector);
}

Rectangle2D operator-(const Vector2D& vector, const Rectangle2D& segment) {
  return Rectangle2D(vector - segment.point00(), vector - segment.point11());
}


} // namespace wigeon
