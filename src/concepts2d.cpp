#include "wigeon/concepts2d.h"


namespace wigeon {

// boost::variant visitor helper classes
namespace {

template <typename T1>
class rotate_visitor : public boost::static_visitor<T1> {
  public:
    explicit rotate_visitor(const Rotation2D& rotation) : rotation(rotation) {}

    template <typename T>
    T1 operator()(const T& object) {
      return rotate(rotation, object);
    }

    const Rotation2D& rotation;
};

template <typename T1>
class rightplus_visitor : public boost::static_visitor<T1> {
  public:
    explicit rightplus_visitor(const Vector2D& vector) : vector(vector) {}

    template <typename T>
    T1 operator()(const T& object) {
      return object + vector;
    }

    const Vector2D& vector;
};

template <typename T1>
class leftplus_visitor : public boost::static_visitor<T1> {
  public:
    explicit leftplus_visitor(const Vector2D& vector) : vector(vector) {}

    template <typename T>
    T1 operator()(const T& object) {
      return vector + object;
    }

    const Vector2D& vector;
};

template <typename T1>
class rightminus_visitor : public boost::static_visitor<T1> {
  public:
    explicit rightminus_visitor(const Vector2D& vector) : vector(vector) {}

    template <typename T>
    T1 operator()(const T& object) {
      return object - vector;
    }

    const Vector2D& vector;
};

template <typename T1>
class leftminus_visitor : public boost::static_visitor<T1> {
  public:
    explicit leftminus_visitor(const Vector2D& vector) : vector(vector) {}

    template <typename T>
    T1 operator()(const T& object) {
      return vector - object;
    }

    const Vector2D& vector;
};

} // anonymous namespace


Curve2D rotate(const Rotation2D& rotation, const Curve2D& curve) {
  rotate_visitor<Curve2D> visitor(rotation);
  return curve.apply_visitor(visitor);
}

FiniteCurve2D rotate(const Rotation2D& rotation, const FiniteCurve2D& curve) {
  rotate_visitor<FiniteCurve2D> visitor(rotation);
  return curve.apply_visitor(visitor);
}

InfiniteCurve2D rotate(const Rotation2D& rotation, const InfiniteCurve2D& curve) {
  rotate_visitor<InfiniteCurve2D> visitor(rotation);
  return curve.apply_visitor(visitor);
}

OpenCurve2D rotate(const Rotation2D& rotation, const OpenCurve2D& curve) {
  rotate_visitor<OpenCurve2D> visitor(rotation);
  return curve.apply_visitor(visitor);
}

ClosedCurve2D rotate(const Rotation2D& rotation, const ClosedCurve2D& curve) {
  rotate_visitor<ClosedCurve2D> visitor(rotation);
  return curve.apply_visitor(visitor);
}

PlotObject2D rotate(const Rotation2D& rotation, const PlotObject2D& obj) {
  rotate_visitor<PlotObject2D> visitor(rotation);
  return obj.apply_visitor(visitor);
}



Curve2D operator+(const Curve2D& curve, const Vector2D& vector) {
  rightplus_visitor<Curve2D> visitor(vector);
  return curve.apply_visitor(visitor);
}

Curve2D operator+(const Vector2D& vector, const Curve2D& curve) {
  leftplus_visitor<Curve2D> visitor(vector);
  return curve.apply_visitor(visitor);
}


FiniteCurve2D operator+(const FiniteCurve2D& curve, const Vector2D& vector) {
  rightplus_visitor<FiniteCurve2D> visitor(vector);
  return curve.apply_visitor(visitor);
}

FiniteCurve2D operator+(const Vector2D& vector, const FiniteCurve2D& curve) {
  leftplus_visitor<FiniteCurve2D> visitor(vector);
  return curve.apply_visitor(visitor);
}


InfiniteCurve2D operator+(const InfiniteCurve2D& curve, const Vector2D& vector) {
  rightplus_visitor<InfiniteCurve2D> visitor(vector);
  return curve.apply_visitor(visitor);
}

InfiniteCurve2D operator+(const Vector2D& vector, const InfiniteCurve2D& curve) {
  leftplus_visitor<InfiniteCurve2D> visitor(vector);
  return curve.apply_visitor(visitor);
}


OpenCurve2D operator+(const OpenCurve2D& curve, const Vector2D& vector) {
  rightplus_visitor<OpenCurve2D> visitor(vector);
  return curve.apply_visitor(visitor);
}

OpenCurve2D operator+(const Vector2D& vector, const OpenCurve2D& curve) {
  leftplus_visitor<OpenCurve2D> visitor(vector);
  return curve.apply_visitor(visitor);
}


ClosedCurve2D operator+(const ClosedCurve2D& curve, const Vector2D& vector) {
  rightplus_visitor<ClosedCurve2D> visitor(vector);
  return curve.apply_visitor(visitor);
}

ClosedCurve2D operator+(const Vector2D& vector, const ClosedCurve2D& curve) {
  leftplus_visitor<ClosedCurve2D> visitor(vector);
  return curve.apply_visitor(visitor);
}


PlotObject2D operator+(const PlotObject2D& object, const Vector2D& vector) {
  rightplus_visitor<PlotObject2D> visitor(vector);
  return object.apply_visitor(visitor);
}

PlotObject2D operator+(const Vector2D& vector, const PlotObject2D& object) {
  leftplus_visitor<PlotObject2D> visitor(vector);
  return object.apply_visitor(visitor);
}



Curve2D operator-(const Curve2D& curve, const Vector2D& vector) {
  rightminus_visitor<Curve2D> visitor(vector);
  return curve.apply_visitor(visitor);
}

FiniteCurve2D operator-(const FiniteCurve2D& curve, const Vector2D& vector) {
  rightminus_visitor<FiniteCurve2D> visitor(vector);
  return curve.apply_visitor(visitor);
}

InfiniteCurve2D operator-(const InfiniteCurve2D& curve, const Vector2D& vector) {
  rightminus_visitor<InfiniteCurve2D> visitor(vector);
  return curve.apply_visitor(visitor);
}

OpenCurve2D operator-(const OpenCurve2D& curve, const Vector2D& vector) {
  rightminus_visitor<OpenCurve2D> visitor(vector);
  return curve.apply_visitor(visitor);
}

ClosedCurve2D operator-(const ClosedCurve2D& curve, const Vector2D& vector) {
  rightminus_visitor<ClosedCurve2D> visitor(vector);
  return curve.apply_visitor(visitor);
}

PlotObject2D operator-(const PlotObject2D& object, const Vector2D& vector) {
  rightminus_visitor<PlotObject2D> visitor(vector);
  return object.apply_visitor(visitor);
}

} // namespace wigeon
