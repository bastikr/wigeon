#pragma once

#include <array>

#include "geomalia/vector2d.h"
#include "geomalia/point2d.h"


namespace geomalia {

struct Rectangle2D {
  Rectangle2D(double xmin, double ymin, double xmax, double ymax);
  Rectangle2D(Point2D pmin, Point2D pmax);

  double width() const {return data[2] - data[0];}
  double height() const {return data[3] - data[1];}

  double xmin() const {return data[0];}
  double xmax() const {return data[2];}
  double ymin() const {return data[1];}
  double ymax() const {return data[3];}

  Point2D point00() const {return Point2D(xmin(), ymin());}
  Point2D point01() const {return Point2D(xmin(), ymax());}
  Point2D point10() const {return Point2D(xmax(), ymin());}
  Point2D point11() const {return Point2D(xmax(), ymax());}

  std::array<double, 4> data;
};

Rectangle2D operator+(const Rectangle2D&, const Vector2D&);
Rectangle2D operator+(const Vector2D&, const Rectangle2D&);

Rectangle2D operator-(const Rectangle2D&, const Vector2D&);
Rectangle2D operator-(const Vector2D&, const Rectangle2D&);

} // namespace geomalia
