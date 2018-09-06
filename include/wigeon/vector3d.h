#pragma once

#include <array>


namespace wigeon {

struct Point3D;

struct Vector3D {
  Vector3D() {}
  Vector3D(double x, double y, double z);
  explicit Vector3D(const Point3D& p);

  double x() const;
  void set_x(double x);

  double y() const;
  void set_y(double y);

  double z() const;
  void set_z(double z);

  double length2() const;
  double length() const;

  std::array<double, 3> data;
};


Vector3D operator+(const Vector3D&, const Vector3D&);

Vector3D operator-(const Vector3D&);
Vector3D operator-(const Vector3D&, const Vector3D&);

Vector3D operator*(const Vector3D&, double);
Vector3D operator*(double, const Vector3D&);
double operator*(const Vector3D&, const Vector3D&);

Vector3D operator/(const Vector3D&, double);


struct UnitVector3D : public Vector3D {
  UnitVector3D() {}
  UnitVector3D(const Vector3D& v) : Vector3D(v/v.length()) {}
  UnitVector3D(double x, double y, double z) : UnitVector3D(Vector3D(x, y, z)) {}
};


Vector3D cross(const Vector3D&, const Vector3D&);

} // namespace wigeon
