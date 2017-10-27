/*! \file rotations.h
  \brief Provides several different representations of rotations.

  There exist the following types:
    - RotationMatrix
    - EulerAngles (ZYX version)
    - AxisAngle
    - Quaternion

  They all can be explicitly converted from one to another and provide a
  common interface:
    - `T::rotate_x(double angle)`
    - `T::rotate_y(double angle)`
    - `T::rotate_z(double angle)`
*/

#include <eigen3/Eigen/Dense>

namespace geometry {

/*!
  \brief 3D rotations related functionality.
*/
namespace rotations {

class RotationMatrix;
class EulerAngles;
class AxisAngle;
class Quaternion;

/*!
  \brief A 3x3 rotation matrix.
*/
class RotationMatrix {
  public:
    RotationMatrix(Eigen::Matrix3d data): data(data) {}
    explicit RotationMatrix(const EulerAngles&);
    explicit RotationMatrix(const AxisAngle&);
    explicit RotationMatrix(const Quaternion&);

    static RotationMatrix rotate_x(double);
    static RotationMatrix rotate_y(double);
    static RotationMatrix rotate_z(double);

    RotationMatrix operator*(const RotationMatrix&);

  // private:
    Eigen::Matrix3d data;
};


//! ZYX Euler angles
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

//! Rotation around the specified axis by the given angle
class AxisAngle {
  public:
    AxisAngle(Eigen::Vector3d axis, double angle): axis(axis), angle(angle) {}
    explicit AxisAngle(const RotationMatrix&);
    explicit AxisAngle(const EulerAngles&);
    explicit AxisAngle(const Quaternion&);

    static AxisAngle rotate_x(double);
    static AxisAngle rotate_y(double);
    static AxisAngle rotate_z(double);

    AxisAngle operator*(const AxisAngle&);

  // private:
    Eigen::Vector3d axis;
    double angle;
};

//! Typical quaternion
class Quaternion {
  public:
    Quaternion(Eigen::Vector4d data): data(data) {}
    explicit Quaternion(const RotationMatrix&);
    explicit Quaternion(const EulerAngles&);
    explicit Quaternion(const AxisAngle&);

    static Quaternion rotate_x(double);
    static Quaternion rotate_y(double);
    static Quaternion rotate_z(double);

    Quaternion operator*(const Quaternion&);

  // private:
    Eigen::Vector4d data;
};

} // namespace rotations

} // namespace geometry