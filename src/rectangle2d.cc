#include "geomalia/rectangle2d.h"


namespace geomalia {

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
  return Rectangle2D(segment.getPoint00() + vector, segment.getPoint11() + vector);
}

Rectangle2D operator+(const Vector2D& vector, const Rectangle2D& segment)  {
  return Rectangle2D(vector + segment.getPoint00(), vector + segment.getPoint11());
}

Rectangle2D operator-(const Rectangle2D& segment, const Vector2D& vector) {
  return Rectangle2D(segment.getPoint00() - vector, segment.getPoint11() - vector);
}

Rectangle2D operator-(const Vector2D& vector, const Rectangle2D& segment) {
  return Rectangle2D(vector - segment.getPoint00(), vector - segment.getPoint11());
}


} // namespace geomalia
