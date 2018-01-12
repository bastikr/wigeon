#pragma once

#include <array>


namespace wigeon {

class Quaternion2D {
  public:
    Quaternion2D(double angle);
    Quaternion2D(double x, double y)
        : data({{x, y}}) {}

    double x() const {return data[0];};
    double y() const {return data[1];};

    Quaternion2D inverse() const;

    std::array<double, 2> data;
};

Quaternion2D operator*(const Quaternion2D&, const Quaternion2D&);


class TransformationMatrix2D {
  public:
    TransformationMatrix2D(const Quaternion2D&);
    std::array<double, 4> data;
};

} // namespace wigeon
