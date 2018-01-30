#pragma once

#include "wigeon/polygon2d.h"
#include "wigeon/polyline2d.h"


namespace wigeon {

Polygon2D douglas_peucker(const Polygon2D&, double eps);
PolyLine2D douglas_peucker(const PolyLine2D&, double eps);

} // namespace wigeon
