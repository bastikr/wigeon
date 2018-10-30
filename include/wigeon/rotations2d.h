#pragma once

#include <array>


namespace wigeon {

class Rotation2D {
  public:
    Rotation2D();
    Rotation2D(double angle);
    Rotation2D(double x, double y);

    double x() const;
    double y() const;

    double angle() const;
    void set_angle(double);

    Rotation2D inverse() const;

    std::array<double, 2> data;
};

Rotation2D operator*(const Rotation2D&, const Rotation2D&);

template<typename T>
T rotate(double angle, const T& object) {
  return rotate(Rotation2D(angle), object);
}


class TransformationMatrix2D {
  public:
    TransformationMatrix2D(const Rotation2D&);
    std::array<double, 4> data;
};

} // namespace wigeon
