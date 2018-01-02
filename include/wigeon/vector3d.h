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


Vector3D operator+(const Vector3D& vector0, const Vector3D& vector1);

Vector3D operator-(const Vector3D& vector);
Vector3D operator-(const Vector3D& vector0, const Vector3D& vector1);

Vector3D operator*(const Vector3D& vector, double a);
Vector3D operator*(double a, const Vector3D& vector);
double operator*(const Vector3D& vector0, const Vector3D& vector1);

Vector3D operator/(const Vector3D& vector, double a);


struct UnitVector3D : public Vector3D {
  UnitVector3D(double x, double y, double z);
  UnitVector3D(const Vector3D& v) : Vector3D(v/v.length()) {}
};


Vector3D cross(const Vector3D& vector0, const Vector3D& vector1);
UnitVector3D cross(const UnitVector3D& vector0, const UnitVector3D& vector1);

} // namespace wigeon
