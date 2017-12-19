#pragma once

#include <array>


namespace geomalia {

struct Vector3D;

struct Point3D {
  Point3D(double x, double y, double z) : data({{x, y, z}}) {}

  double x() const {return data[0];}
  double y() const {return data[1];}
  double z() const {return data[2];}

  Point3D operator+(const Vector3D& vector) const;
  Point3D operator-(const Vector3D& vector) const;
  Vector3D operator-(const Point3D& point) const;

  std::array<double, 3> data;
};

} // namespace geomalia
