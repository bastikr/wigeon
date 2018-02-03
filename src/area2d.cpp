#include "wigeon/area2d.h"


namespace wigeon {

Area2D operator+(const Area2D& area, const Vector2D& vector) {
  Area2D result;
  result.exterior_curves = area.exterior_curves + vector;
  result.interior_curves = area.interior_curves + vector;
  return result;
}

Area2D operator+(const Vector2D& vector, const Area2D& area) {
  Area2D result;
  result.exterior_curves = vector + area.exterior_curves;
  result.interior_curves = vector + area.interior_curves;
  return result;
}


Area2D operator-(const Area2D& area, const Vector2D& vector) {
  Area2D result;
  result.exterior_curves = area.exterior_curves - vector;
  result.interior_curves = area.interior_curves - vector;
  return result;
}

Area2D operator-(const Vector2D& vector, const Area2D& area) {
  Area2D result;
  result.exterior_curves = vector - area.exterior_curves;
  result.interior_curves = vector - area.interior_curves;
  return result;
}


Area2D rotate(const Rotation2D& rotation, const Area2D& area) {
  Area2D result;
  result.exterior_curves = rotate(rotation, area.exterior_curves);
  result.interior_curves = rotate(rotation, area.interior_curves);
  return result;
}

} // namespace wigeon
