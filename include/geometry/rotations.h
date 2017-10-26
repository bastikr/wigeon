#include <eigen3/Eigen/Dense>

namespace geometry {

namespace rotations {

class RoationMatrix;
class EulerAngles;
class AxisAngle;
class Quaternion;


class RotationMatrix {
  public:
    RotationMatrix(Eigen::Matrix3d data): data(data) {}
    explicit RotationMatrix(const EulerAngles&);
    explicit RotationMatrix(const AxisAngle&);
    explicit RotationMatrix(const Quaternion&);

    static RotationMatrix rotate_x(double);
    static RotationMatrix rotate_y(double);
    static RotationMatrix rotate_z(double);

  // private:
    Eigen::Matrix3d data;
};


class EulerAngles {
  public:
    EulerAngles(Eigen::Vector3d angles): angles(angles) {}
    explicit EulerAngles(const RotationMatrix&);
    explicit EulerAngles(const AxisAngle&);
    explicit EulerAngles(const Quaternion&);

    static EulerAngles rotate_x(double);
    static EulerAngles rotate_y(double);
    static EulerAngles rotate_z(double);

  // private:
    Eigen::Vector3d angles;
};


class AxisAngle {
  public:
    AxisAngle(Eigen::Vector3d axis, double angle): axis(axis), angle(angle) {}
    explicit AxisAngle(const RotationMatrix&);
    explicit AxisAngle(const EulerAngles&);
    explicit AxisAngle(const Quaternion&);

    static AxisAngle rotate_x(double);
    static AxisAngle rotate_y(double);
    static AxisAngle rotate_z(double);

  // private:
    Eigen::Vector3d axis;
    double angle;
};


class Quaternion {
  public:
    Quaternion(Eigen::Vector4d data): data(data) {}
    explicit Quaternion(const RotationMatrix&);
    explicit Quaternion(const EulerAngles&);
    explicit Quaternion(const AxisAngle&);

    static Quaternion rotate_x(double);
    static Quaternion rotate_y(double);
    static Quaternion rotate_z(double);

  // private:
    Eigen::Vector4d data;
};

} // namespace rotations

} // namespace geometry