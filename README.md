# Geometry 3D

A library for manipulating 3 dimensional vectors.

This library is mostly written to learn about a few C++ related things:

  * C++ project directory structures
  * cmake
  * unittests with googletest
  * automatic integration with travis-ci
  * doxygen

  
## Development status

  * Linux build: [![Travis build status][travis-img]][travis-url]


## Documentation

At the moment it provides only functionality regarding rotations:

  * Rotation matrices: `geometry::rotations::RotationMatrix`
  * ZYX euler angles: `geometry::rotations::EulerAngles`
  * Axis-angle approach: `geometry::rotations::AxisAngle`
  * Quaternions: `geometry::rotations::Quaternion`


[travis-url]: https://travis-ci.org/bastikr/geometry
[travis-img]: https://travis-ci.org/bastikr/geometry.svg?branch=master
