#include "geomalia/linesegment2d.h"

namespace geomalia {

Point2D LineSegment2D::getPoint0() const {
    return Point2D(data[0], data[2]);
  }

Point2D LineSegment2D::getPoint1() const {
  return Point2D(data[1], data[3]);
}

LineSegment2D operator+(const LineSegment2D& segment, const Vector2D& vector) {
  return LineSegment2D(segment.getPoint0() + vector, segment.getPoint1() + vector);
}

LineSegment2D operator+(const Vector2D& vector, const LineSegment2D& segment)  {
  return LineSegment2D(vector + segment.getPoint0(), vector + segment.getPoint1());
}

LineSegment2D operator-(const LineSegment2D& segment, const Vector2D& vector) {
  return LineSegment2D(segment.getPoint0() - vector, segment.getPoint1() - vector);
}

LineSegment2D operator-(const Vector2D& vector, const LineSegment2D& segment) {
  return LineSegment2D(vector - segment.getPoint0(), vector - segment.getPoint1());
}


} // namespace geomalia
