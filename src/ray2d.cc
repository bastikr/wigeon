#include "geomalia/ray2d.h"

namespace geomalia {

Ray2D operator+(const Ray2D& ray, const Vector2D& vector) {
  return Ray2D(ray.getPoint() + vector, ray.getDirection());
}

Ray2D operator+(const Vector2D& vector, const Ray2D& ray) {
  return Ray2D(vector + ray.getPoint(), ray.getDirection());
}

Ray2D operator-(const Ray2D& ray, const Vector2D& vector) {
  return Ray2D(ray.getPoint() - vector, ray.getDirection());
}

Ray2D operator-(const Vector2D& vector, const Ray2D& ray) {
  return Ray2D(vector - ray.getPoint(), ray.getDirection());
}

} // namespace geomalia
