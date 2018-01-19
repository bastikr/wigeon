#include "wigeon/doublelinesegment2d.h"

#include <cmath>


namespace wigeon {

DoubleLineSegment2D operator+(const DoubleLineSegment2D& segment, const Vector2D& vector) {
  return DoubleLineSegment2D(segment.point0() + vector, segment.point1() + vector, segment.point2() + vector);
}

DoubleLineSegment2D operator+(const Vector2D& vector, const DoubleLineSegment2D& segment)  {
  return DoubleLineSegment2D(vector + segment.point0(), vector + segment.point1(), vector + segment.point2());
}

DoubleLineSegment2D operator-(const DoubleLineSegment2D& segment, const Vector2D& vector) {
  return DoubleLineSegment2D(segment.point0() - vector, segment.point1() - vector, segment.point2() - vector);
}

DoubleLineSegment2D operator-(const Vector2D& vector, const DoubleLineSegment2D& segment) {
  return DoubleLineSegment2D(vector - segment.point0(), vector - segment.point1(), vector - segment.point2());
}

DoubleLineSegment2D rotate(const Rotation2D& R, const DoubleLineSegment2D& segment) {
  return DoubleLineSegment2D(rotate(R, segment.point0()), rotate(R, segment.point1()), rotate(R, segment.point2()));
}

} // namespace wigeon
