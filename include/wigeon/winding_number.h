#pragma once

#include "wigeon/point2d.h"
#include "wigeon/polygon2d.h"


namespace wigeon {

int winding_number(const Point2D&, const Polygon2D&);

} // namespace wigeon