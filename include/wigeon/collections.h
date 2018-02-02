#pragma once

#include <list>

#include "wigeon/concepts.h"


namespace wigeon {

using Curves2D = std::list<Curve2D>;
using ClosedCurves2D = std::list<ClosedCurve2D>;
using PlotObjects2D = std::list<PlotObject2D>;

} // namespace wigeon
