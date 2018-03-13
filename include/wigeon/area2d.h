#pragma once

#include "wigeon/rotations2d.h"
#include "wigeon/vector2d.h"
#include "wigeon/collections.h"


namespace wigeon {

struct Area2D {
  ClosedCurves2D exterior_curves;
  ClosedCurves2D interior_curves;
};

Area2D operator+(const Area2D&, const Vector2D&);
Area2D operator+(const Vector2D&, const Area2D&);

Area2D operator-(const Area2D&, const Vector2D&);

Area2D rotate(const Rotation2D&, const Area2D&);

} // namespace wigeon
