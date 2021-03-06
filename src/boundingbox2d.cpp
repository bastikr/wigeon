#include "wigeon/boundingbox2d.h"

#include <cmath>
#include <limits>


namespace wigeon {

const double NaN = std::numeric_limits<double>::quiet_NaN();

BoundingBox2D::BoundingBox2D()
    : origin_(NaN, NaN), width_(NaN), height_(NaN) {}

BoundingBox2D::BoundingBox2D(const Point2D& origin, double width, double height)
    : origin_(origin), width_(width), height_(height) {}

BoundingBox2D::BoundingBox2D(const Point2D& p00, const Point2D& p11)
    : origin_((p00.x() + p11.x())/2, (p00.y() + p11.y())/2),
      width_(p11.x() - p00.x()), height_(p11.y() - p00.y()) {}

BoundingBox2D::BoundingBox2D(double x0, double y0, double x1, double y1)
    : origin_((x0 + x1)/2, (y0 + y1)/2),
      width_(x1 - x0), height_(y1 - y0) {}

Point2D BoundingBox2D::origin() const {
  return origin_;
}

void BoundingBox2D::set_origin(const Point2D& p) {
  origin_ = p;
}

void BoundingBox2D::set_origin(double x, double y) {
  origin_.set_x(x);
  origin_.set_y(y);
}

double BoundingBox2D::width() const {
  return width_;
}

void BoundingBox2D::set_width(double width) {
  width_ = width;
}

double BoundingBox2D::height() const {
  return height_;
}

void BoundingBox2D::set_height(double height) {
  height_ = height;
}
double BoundingBox2D::area() const {
  return width_*height_;
}

bool BoundingBox2D::isnan() const {
  return std::isnan(width_) || std::isnan(height_);
}

double BoundingBox2D::xmin() const {
  return origin_.x() - 0.5*width_;
}

double BoundingBox2D::xmax() const {
  return origin_.x() + 0.5*width_;
}

double BoundingBox2D::ymin() const {
  return origin_.y() - 0.5*height_;
}

double BoundingBox2D::ymax() const {
  return origin_.y() + 0.5*height_;
}


BoundingBox2D operator+(const BoundingBox2D& box, const Vector2D& vector) {
  return BoundingBox2D(box.origin() + vector, box.width(), box.height());
}

BoundingBox2D operator+(const Vector2D& vector, const BoundingBox2D& box)  {
  return BoundingBox2D(vector + box.origin(), box.width(), box.height());
}

BoundingBox2D operator-(const BoundingBox2D& box, const Vector2D& vector) {
  return BoundingBox2D(box.origin() - vector, box.width(), box.height());
}

bool overlap(const BoundingBox2D& box0, const BoundingBox2D& box1) {
  if (box0.isnan() || box1.isnan()) {
    return false;
  }
  return std::abs(box0.origin().x() - box1.origin().x()) < (box0.width() + box1.width())/2
      && std::abs(box0.origin().y() - box1.origin().y()) < (box0.height() + box1.height())/2;
}

BoundingBox2D combine(const BoundingBox2D& box0, const BoundingBox2D& box1) {
  if (box0.isnan())
    return box1;
  if (box1.isnan())
    return box0;
  double xmin = std::min(box0.xmin(), box1.xmin());
  double ymin = std::min(box0.ymin(), box1.ymin());
  double xmax = std::max(box0.xmax(), box1.xmax());
  double ymax = std::max(box0.ymax(), box1.ymax());
  return BoundingBox2D(xmin, ymin, xmax, ymax);
}


BoundingBox2D boundingbox(const LineSegment2D& segment) {
  double x = 0.5*(segment.x0() + segment.x1());
  double y = 0.5*(segment.y0() + segment.y1());
  double width = std::abs(segment.x0() - segment.x1());
  double height = std::abs(segment.y0() - segment.y1());
  return BoundingBox2D(Point2D(x, y), width, height);
}

BoundingBox2D boundingbox(const Triangle2D& triangle) {
  Point2D p0 = triangle.point0();
  Point2D p1 = triangle.point1();
  Point2D p2 = triangle.point2();

  double xmin = p0.x();
  double xmax = p0.x();
  double ymin = p0.y();
  double ymax = p0.y();

  xmin = std::min(xmin, p1.x());
  ymin = std::min(ymin, p1.y());
  xmax = std::max(xmax, p1.x());
  ymax = std::max(ymax, p1.y());

  xmin = std::min(xmin, p2.x());
  ymin = std::min(ymin, p2.y());
  xmax = std::max(xmax, p2.x());
  ymax = std::max(ymax, p2.y());

  return BoundingBox2D(xmin, ymin, xmax, ymax);
}

BoundingBox2D boundingbox(const Rectangle2D& reactangle) {
  Point2D p0 = reactangle.point00();
  Point2D p1 = reactangle.point01();
  Point2D p2 = reactangle.point10();
  Point2D p3 = reactangle.point11();

  double xmin = p0.x();
  double xmax = p0.x();
  double ymin = p0.y();
  double ymax = p0.y();

  xmin = std::min(xmin, p1.x());
  ymin = std::min(ymin, p1.y());
  xmax = std::max(xmax, p1.x());
  ymax = std::max(ymax, p1.y());

  xmin = std::min(xmin, p2.x());
  ymin = std::min(ymin, p2.y());
  xmax = std::max(xmax, p2.x());
  ymax = std::max(ymax, p2.y());

  xmin = std::min(xmin, p3.x());
  ymin = std::min(ymin, p3.y());
  xmax = std::max(xmax, p3.x());
  ymax = std::max(ymax, p3.y());

  return BoundingBox2D(xmin, ymin, xmax, ymax);
}

BoundingBox2D boundingbox(const Circle2D& circle) {
  return BoundingBox2D(circle.origin(), 2*circle.radius(), 2*circle.radius());
}

BoundingBox2D boundingbox(const Polygon2D& polygon) {
  double xmin = std::numeric_limits<double>::infinity();
  double xmax = -std::numeric_limits<double>::infinity();
  double ymin = std::numeric_limits<double>::infinity();
  double ymax = -std::numeric_limits<double>::infinity();

  for (auto& point: polygon.points) {
    xmin = std::min(xmin, point.x());
    ymin = std::min(ymin, point.y());
    xmax = std::max(xmax, point.x());
    ymax = std::max(ymax, point.y());
  }

  return BoundingBox2D(xmin, ymin, xmax, ymax);
}

BoundingBox2D boundingbox(const PolyLine2D& polyline) {
  double xmin = std::numeric_limits<double>::infinity();
  double xmax = -std::numeric_limits<double>::infinity();
  double ymin = std::numeric_limits<double>::infinity();
  double ymax = -std::numeric_limits<double>::infinity();

  for (auto& point: polyline.points) {
    xmin = std::min(xmin, point.x());
    ymin = std::min(ymin, point.y());
    xmax = std::max(xmax, point.x());
    ymax = std::max(ymax, point.y());
  }

  return BoundingBox2D(xmin, ymin, xmax, ymax);
}


namespace {

class boundingbox_visitor : public boost::static_visitor<BoundingBox2D> {
  public:
    template <typename T>
    BoundingBox2D operator()(const T& object) {
      return boundingbox(object);
    }
};

} // anonymous namespace

BoundingBox2D boundingbox(const FiniteCurve2D& curve) {
  boundingbox_visitor visitor;
  return curve.apply_visitor(visitor);
}


BoundingBox2D boundingbox(const Area2D& area) {
  BoundingBox2D box;
  for (auto& curve: area.exterior_curves) {
    box = combine(box, boundingbox(curve));
  }
  return box;
}

} // namespace wigeon
