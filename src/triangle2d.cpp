#include "wigeon/triangle2d.h"

#include <cmath>


namespace wigeon {

Triangle2D::Triangle2D(const Point2D& p0, const Point2D& p1, const Point2D& p2)
    : data{{p0.x(), p0.y(), p1.x(), p1.y(), p2.x(), p2.y()}} {}

Point2D Triangle2D::point0() const {
  return Point2D(data[0], data[1]);
}

Point2D Triangle2D::point1() const {
  return Point2D(data[2], data[3]);
}

Point2D Triangle2D::point2() const {
  return Point2D(data[4], data[5]);
}

double Triangle2D::length() const {
  return (point1() - point0()).length()
       + (point2() - point1()).length()
       + (point0() - point2()).length();
}

double Triangle2D::area() const {
  return std::abs(cross(point1()-point0(), point2()-point0()))/2;
}

Triangle2D Triangle2D::reverse() const {
  return Triangle2D(point2(), point1(), point0());
}

Triangle2D operator+(const Triangle2D& triangle, const Vector2D& vector) {
  return Triangle2D(triangle.point0() + vector,
                    triangle.point1() + vector,
                    triangle.point2() + vector);
}

Triangle2D operator+(const Vector2D& vector, const Triangle2D& triangle) {
  return Triangle2D(vector + triangle.point0(),
                    vector + triangle.point1(),
                    vector + triangle.point2());
}

Triangle2D operator-(const Triangle2D& triangle, const Vector2D& vector) {
  return Triangle2D(triangle.point0() - vector,
                    triangle.point1() - vector,
                    triangle.point2() - vector);
}

Triangle2D rotate(const Rotation2D& R, const Triangle2D& triangle) {
  return Triangle2D(rotate(R, triangle.point0()),
                    rotate(R, triangle.point1()),
                    rotate(R, triangle.point2()));
}

} // namespace wigeon
