#pragma once

#include <array>

#include "wigeon/vector2d.h"
#include "wigeon/point2d.h"


namespace wigeon {

struct BoundingBox2D {
  BoundingBox2D(double xmin, double ymin, double xmax, double ymax);
  BoundingBox2D(Point2D pmin, Point2D pmax);

  Point2D origin() const {return Point2D((data[0]+data[2])/2, (data[1]+data[3])/2);}
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

BoundingBox2D operator+(const BoundingBox2D&, const Vector2D&);
BoundingBox2D operator+(const Vector2D&, const BoundingBox2D&);

BoundingBox2D operator-(const BoundingBox2D&, const Vector2D&);
BoundingBox2D operator-(const Vector2D&, const BoundingBox2D&);

bool overlap(const BoundingBox2D&, const BoundingBox2D&);

} // namespace wigeon
