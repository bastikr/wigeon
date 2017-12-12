#pragma once

#include <array>
#include <vector>

#include <boost/optional.hpp>


namespace geometry {

struct Vector2D;

struct Point2D {
  Point2D(double x, double y) : data({{x, y}}) {}

  double x() const {return data[0];}
  double y() const {return data[1];}

  Point2D operator+(const Vector2D& vector) const;
  Point2D operator-(const Vector2D& vector) const;
  Vector2D operator-(const Point2D& point) const;

  std::array<double, 2> data;
};


struct Vector2D {
  Vector2D(double x, double y) : data({{x, y}}) {}

  double x() const {return data[0];}
  double y() const {return data[1];}

  Point2D operator+(Point2D point) const;
  Vector2D operator+(Vector2D vector) const;

  Vector2D operator-() const;
  Point2D operator-(Point2D point) const;
  Vector2D operator*(double a) const;
  double operator*(const Vector2D& vector) const;
  Vector2D operator/(double a) const;

  std::array<double, 2> data;
};


struct Line2D {
  Line2D(Point2D point, Vector2D direction) : point(point), direction(direction) {}
  Line2D(Point2D point0, Point2D point1) : point(point0), direction(point1-point0) {}

  Point2D getPoint() const {return point;}
  Vector2D getDirection() const {return direction;}

  Line2D operator+(const Vector2D&) const;
  Line2D operator-(const Vector2D&) const;

  Point2D point;
  Vector2D direction;
};

struct Ray2D {
  Ray2D(Point2D point, Vector2D direction): point(point), direction(direction) {}
  Ray2D(Point2D point0, Point2D point1) : point(point0), direction(point1-point0) {}

  Point2D getPoint() const {return point;}
  Vector2D getDirection() const {return direction;}

  Ray2D operator+(const Vector2D&) const;
  Ray2D operator-(const Vector2D&) const;

  Point2D point;
  Vector2D direction;
};

struct LineSegment2D {
  LineSegment2D(const LineSegment2D& segment)
      : data(segment.data) {}

  LineSegment2D(const Point2D& p0, const Point2D& p1)
      : data({{p0.x(), p1.x(), p0.y(), p1.y()}}) {}

  LineSegment2D(double x0, double y0, double x1, double y1)
      : data({{x0, x1, y0, y1}}) {}

  double x0() const {return data[0];}
  double y0() const {return data[1];}
  double x1() const {return data[2];}
  double y1() const {return data[3];}

  Point2D getPoint0() const;
  Point2D getPoint1() const;

  std::array<double, 4> data;
};

struct Circle2D {
  Point2D center;
  double radius;
};

struct Polygon2D {
  void append(const Point2D& point);
  void append(double x, double y);
  void append(const LineSegment2D& segment);

  int size() const;

  boost::optional<Point2D> getPoint(int i) const;
  boost::optional<LineSegment2D> getLineSegment(int i) const;

  std::vector<double> data_x;
  std::vector<double> data_y;
};


double cross(const Vector2D& vector0, const Vector2D& vector1);


double distance2(const Point2D& point0, const Point2D& point1);

double distance2(const Point2D& point0, const LineSegment2D& segment0);
double distance2(const LineSegment2D& segment0, const Point2D& point0);

double distance2(const Line2D& line, const Point2D& point);
double distance2(const Point2D& point, const Line2D& line);

double distance2(const LineSegment2D& segment0, const LineSegment2D& segment1);

double distance2(const Point2D& point0, const Polygon2D& polygon0);
double distance2(const Polygon2D& polygon0, const Point2D& point0);

double distance2(const LineSegment2D& segment, const Polygon2D& polygon);
double distance2(const Polygon2D& polygon, const LineSegment2D& segment);

double distance2(const Polygon2D& polygon0, const Polygon2D& polygon1);


} // namespace geometry
