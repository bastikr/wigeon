#include "wigeon/ray2d.h"

namespace wigeon {

Ray2D operator+(const Ray2D& ray, const Vector2D& vector) {
  return Ray2D(ray.point() + vector, ray.direction());
}

Ray2D operator+(const Vector2D& vector, const Ray2D& ray) {
  return Ray2D(vector + ray.point(), ray.direction());
}

Ray2D operator-(const Ray2D& ray, const Vector2D& vector) {
  return Ray2D(ray.point() - vector, ray.direction());
}

Ray2D operator-(const Vector2D& vector, const Ray2D& ray) {
  return Ray2D(vector - ray.point(), ray.direction());
}

} // namespace wigeon
