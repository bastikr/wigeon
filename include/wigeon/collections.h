#pragma once

#include <list>

#include "wigeon/rotations2d.h"
#include "wigeon/vector2d.h"
#include "wigeon/concepts2d.h"


namespace wigeon {

using Curves2D = std::list<Curve2D>;
using ClosedCurves2D = std::list<ClosedCurve2D>;
using PlotObjects2D = std::list<PlotObject2D>;

template <typename T>
std::list<T> operator+(const Vector2D&, const std::list<T>&);

template <typename T>
std::list<T> operator+(const std::list<T>&, const Vector2D&);

template <typename T>
std::list<T> operator-(const std::list<T>&, const Vector2D&);

template <typename T>
std::list<T> rotate(const Rotation2D&, const std::list<T>&);



template <typename T>
std::list<T> operator+(const Vector2D& vector, const std::list<T>& objects) {
  std::list<T> result;
  for (auto& object: objects) {
    result.push_back(vector + object);
  }
  return result;
}

template <typename T>
std::list<T> operator+(const std::list<T>& objects, const Vector2D& vector) {
  std::list<T> result;
  for (auto& object: objects) {
    result.push_back(object + vector);
  }
  return result;
}

template <typename T>
std::list<T> operator-(const std::list<T>& objects, const Vector2D& vector) {
  std::list<T> result;
  for (auto& object: objects) {
    result.push_back(object - vector);
  }
  return result;
}


template <typename T>
std::list<T> rotate(const Rotation2D& rotation, const std::list<T>& objects) {
  std::list<T> result;
  for (auto& object: objects) {
    result.push_back(rotate(rotation, object));
  }
  return result;
}

} // namespace wigeon
