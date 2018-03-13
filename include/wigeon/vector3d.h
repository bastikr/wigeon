#pragma once

#include <array>


namespace wigeon {

struct Vector3D {
  Vector3D(double x, double y, double z) : data({{x, y, z}}) {}

  double x() const {return data[0];}
  double y() const {return data[1];}
  double z() const {return data[2];}

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
  UnitVector3D(const Vector3D& v) : Vector3D(v/v.length()) {}
  UnitVector3D(double x, double y, double z) : UnitVector3D(Vector3D(x, y, z)) {}
};


Vector3D cross(const Vector3D&, const Vector3D&);

} // namespace wigeon
