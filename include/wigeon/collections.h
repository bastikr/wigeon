#pragma once

#include <list>
#include <boost/variant.hpp>

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

#include "wigeon/point3d.h"
#include "wigeon/vector3d.h"


namespace wigeon {

using Curve2D = boost::variant<Line2D, Ray2D, LineSegment2D, Rectangle2D, Circle2D>;
using Area2D = boost::variant<Rectangle2D, Circle2D, Polygon2D>;

using Curves2D = std::list<Curve2D>;
using Areas2D = std::list<Area2D>;

} // namespace wigeon
