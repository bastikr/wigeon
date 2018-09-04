#include "wigeon/rectangle2d.h"

#include <cmath>


namespace wigeon {

Rectangle2D::Rectangle2D(const Point2D& origin, double width, double height, const Rotation2D& rotation)
    : origin_(origin), width_(width), height_(height), rotation_(rotation) {}

Rectangle2D::Rectangle2D(const Point2D& point00, const Point2D& point11, const Rotation2D& rotation)
    : origin_(point00 + 0.5*(point11 - point00)),
      width_(point11.x()-point00.x()),
      height_(point11.y()-point00.y()),
      rotation_(rotation) {}

Rectangle2D::Rectangle2D(double x0, double y0, double x1, double y1, const Rotation2D& rotation)
    : origin_(0.5*x0 + 0.5*x1, 0.5*y0 + 0.5*y1),
      width_(x1 - x0),
      height_(y1 - y0),
      rotation_(rotation) {}


void Rectangle2D::set_origin(const Point2D& p) {
  origin_ = p;
}

void Rectangle2D::set_origin(double x, double y) {
  origin_.set_x(x);
  origin_.set_y(y);
}

void Rectangle2D::set_width(double width) {
  width_ = width;
}

void Rectangle2D::set_height(double height) {
  height_ = height;
}

void Rectangle2D::set_rotation(const Rotation2D& rotation) {
  rotation_ = rotation;
}

double Rectangle2D::length() const {
  return (point10()-point00()).length()
       + (point11()-point10()).length()
       + (point01()-point11()).length()
       + (point00()-point01()).length();
}

double Rectangle2D::area() const {
  return height()*width();
}

Rectangle2D operator+(const Rectangle2D& rectangle, const Vector2D& vector) {
  return Rectangle2D(rectangle.origin() + vector, rectangle.width(), rectangle.height(), rectangle.rotation());
}

Rectangle2D operator+(const Vector2D& vector, const Rectangle2D& rectangle)  {
  return Rectangle2D(vector + rectangle.origin(), rectangle.width(), rectangle.height(), rectangle.rotation());
}

Rectangle2D operator-(const Rectangle2D& rectangle, const Vector2D& vector) {
  return Rectangle2D(rectangle.origin() - vector, rectangle.width(), rectangle.height(), rectangle.rotation());
}


Rectangle2D rotate(const Rotation2D& rotation, const Rectangle2D& rectangle) {
  return Rectangle2D(rotate(rotation, rectangle.origin()),
                    rectangle.width(), rectangle.height(),
                    rotation*rectangle.rotation());
}

} // namespace wigeon
