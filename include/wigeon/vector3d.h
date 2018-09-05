#pragma once

#include <array>


namespace wigeon {

struct Point3D;

struct Vector3D {
  Vector3D() {}
  Vector3D(double x, double y, double z) : data({{x, y, z}}) {}
  explicit Vector3D(const Point3D& p);

  double x() const {return data[0];}
  void set_x(double x) {data[0] = x;}

  double y() const {return data[1];}
  void set_y(double y) {data[1] = y;}

  double z() const {return data[2];}
  void set_z(double z) {data[2] = z;}

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
