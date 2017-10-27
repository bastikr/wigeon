# Geometry 3D

A library for manipulating 3 dimensional vectors.

This library is mostly written to learn about a few C++ related things:

  * C++ project directory structures
  * cmake
  * unittests with googletest
  * automatic integration with travis-ci
  * doxygen

  
## Development status

  * Linux/Mac build: [![Travis build status][travis-img]][travis-url]


## Documentation

At the moment it provides only functionality regarding rotations:

  * rotation matrices: `RotationMatrix`
  * ZYX euler angles: `EulerAngles`
  * axis-angle approach: `AxisAngle`
  * quaternions: `Quaternion`


[travis-url]: https://travis-ci.org/bastikr/geometry
[travis-img]: https://travis-ci.org/bastikr/geometry.svg?branch=master
