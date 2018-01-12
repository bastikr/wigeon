#pragma once

#include <array>


namespace wigeon {

class Rotation2D {
  public:
    Rotation2D(double angle);
    Rotation2D(double x, double y)
        : data({{x, y}}) {}

    double x() const {return data[0];};
    double y() const {return data[1];};

    Rotation2D inverse() const;

    std::array<double, 2> data;
};

Rotation2D operator*(const Rotation2D&, const Rotation2D&);


class TransformationMatrix2D {
  public:
    TransformationMatrix2D(const Rotation2D&);
    std::array<double, 4> data;
};

} // namespace wigeon
