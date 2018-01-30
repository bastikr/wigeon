#pragma once

#include <ostream>

#include "wigeon/point1d.h"
#include "wigeon/vector1d.h"

#include "wigeon/point2d.h"
#include "wigeon/vector2d.h"
#include "wigeon/line2d.h"
#include "wigeon/ray2d.h"
#include "wigeon/linesegment2d.h"
#include "wigeon/rectangle2d.h"
#include "wigeon/circle2d.h"
#include "wigeon/polygon2d.h"
#include "wigeon/polyline2d.h"

#include "wigeon/point3d.h"
#include "wigeon/vector3d.h"


namespace wigeon {

std::ostream& operator<<(std::ostream&, const Point1D&);
std::ostream& operator<<(std::ostream&, const Vector1D&);

std::ostream& operator<<(std::ostream&, const Point2D&);
std::ostream& operator<<(std::ostream&, const Vector2D&);
std::ostream& operator<<(std::ostream&, const Line2D&);
std::ostream& operator<<(std::ostream&, const Ray2D&);
std::ostream& operator<<(std::ostream&, const LineSegment2D&);
std::ostream& operator<<(std::ostream&, const Rectangle2D&);
std::ostream& operator<<(std::ostream&, const Circle2D&);
std::ostream& operator<<(std::ostream&, const Polygon2D&);
std::ostream& operator<<(std::ostream&, const PolyLine2D&);

std::ostream& operator<<(std::ostream&, const Point3D&);
std::ostream& operator<<(std::ostream&, const Vector3D&);

} // namespace wigeon
