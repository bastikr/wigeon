#pragma once

#include <boost/variant.hpp>
#include <vector>

#include "wigeon/point2d.h"
#include "wigeon/line2d.h"
#include "wigeon/ray2d.h"
#include "wigeon/linesegment2d.h"
#include "wigeon/polygon2d.h"


namespace wigeon {

template <typename Geometry, typename ResultGeometry>
struct IntersectionDescription;


// Line2D
template<>
struct IntersectionDescription<Line2D, Point2D> {
  explicit IntersectionDescription(double r) : r(r) {}
  double r;
};

template<>
struct IntersectionDescription<Line2D, LineSegment2D> {
  IntersectionDescription(double r0, double r1) : r0(r0), r1(r1) {}
  double r0;
  double r1;
};

template<>
struct IntersectionDescription<Line2D, Ray2D> {
  IntersectionDescription(double r, bool direction) : r(r), direction(direction) {}
  double r;
  bool direction;
};

template<>
struct IntersectionDescription<Line2D, Line2D> {};


// Ray2D
template<>
struct IntersectionDescription<Ray2D, Point2D> {
  explicit IntersectionDescription(double r) : r(r) {}
  double r;
};

template<>
struct IntersectionDescription<Ray2D, LineSegment2D> {
  IntersectionDescription(double r0, double r1) : r0(r0), r1(r1) {}
  double r0;
  double r1;
};

template<>
struct IntersectionDescription<Ray2D, Ray2D> {
  explicit IntersectionDescription(double r) : r(r) {}
  double r;
};


// LineSegment2D
template<>
struct IntersectionDescription<LineSegment2D, Point2D> {
  using ResultType = Point2D;

  explicit IntersectionDescription(double r) : r(r) {}
  double r;
};

template<>
struct IntersectionDescription<LineSegment2D, LineSegment2D> {
  using ResultType = LineSegment2D;

  IntersectionDescription(double r0, double r1) : r0(r0), r1(r1) {}
  double r0;
  double r1;
};


// Polygon2D
template<>
struct IntersectionDescription<Polygon2D, Point2D> {
  IntersectionDescription(size_t index, const IntersectionDescription<LineSegment2D, Point2D>& d)
      : index(index), segment(d) {}
  size_t index;
  IntersectionDescription<LineSegment2D, Point2D> segment;
};

template<>
struct IntersectionDescription<Polygon2D, LineSegment2D> {
  IntersectionDescription(size_t index, const IntersectionDescription<LineSegment2D, LineSegment2D>& d)
      : index(index), segment(d) {}
  size_t index;
  IntersectionDescription<LineSegment2D, LineSegment2D> segment;
};


template <typename Geometry0, typename Geometry1, typename ResultGeometry>
struct Intersection {
  using Description0 = IntersectionDescription<Geometry0, ResultGeometry>;
  using Description1 = IntersectionDescription<Geometry1, ResultGeometry>;
  using ResultType = ResultGeometry;

  Intersection(const ResultGeometry& result, const Description0& description0, const Description1& description1)
      : result(result), description0(description0), description1(description1) {}

  ResultGeometry result;
  Description0 description0;
  Description1 description1;

  Intersection<Geometry1, Geometry0, ResultGeometry> flip() const {
    return Intersection<Geometry1, Geometry0, ResultGeometry>(result, description1, description0);
  }
};


template <typename Geometry0, typename Geometry1>
struct IntersectionResultTypes {
  using types = typename IntersectionResultTypes<Geometry1, Geometry0>::types;
};

template<class Geometry0, class Geometry1, class L> struct IntersectionTypes_impl;

template<class Geometry0, class Geometry1, template<class...> class L, class... T>
    struct IntersectionTypes_impl<Geometry0, Geometry1, L<T...>>
{
    using type = L<Intersection<Geometry0, Geometry1, T>...>;
};

template <class Geometry0, class Geometry1>
  using IntersectionTypes = typename IntersectionTypes_impl<
                                Geometry0, Geometry1,
                                typename IntersectionResultTypes<Geometry0, Geometry1>::types>::type;




template <typename Geometry0, typename Geometry1>
class flip_visitor : public boost::static_visitor<IntersectionTypes<Geometry1, Geometry0>> {
  public:

    template <typename ResultGeometry>
    Intersection<Geometry1, Geometry0, ResultGeometry>
    operator()(const Intersection<Geometry0, Geometry1, ResultGeometry>& intersection) {
      return intersection.flip();
    }
};


// Line2D
template<>
struct IntersectionResultTypes<Line2D, Line2D> {
  using types = boost::variant<Point2D, Line2D>;
};

std::vector<IntersectionTypes<Line2D, Line2D>> intersections(const Line2D&, const Line2D&);


// Ray2D
template<>
struct IntersectionResultTypes<Ray2D, Line2D> {
  using types = boost::variant<Point2D, Ray2D>;
};

template<>
struct IntersectionResultTypes<Ray2D, Ray2D> {
  using types = boost::variant<Point2D, LineSegment2D, Ray2D>;
};

std::vector<IntersectionTypes<Ray2D, Ray2D>> intersections(const Ray2D&, const Ray2D&);
std::vector<IntersectionTypes<Ray2D, Line2D>> intersections(const Ray2D&, const Line2D&);
std::vector<IntersectionTypes<Line2D, Ray2D>> intersections(const Line2D&, const Ray2D&);


// LineSegment2D
template<>
struct IntersectionResultTypes<LineSegment2D, Line2D> {
  using types = boost::variant<Point2D, LineSegment2D>;
};

template<>
struct IntersectionResultTypes<LineSegment2D, Ray2D> {
  using types = boost::variant<Point2D, LineSegment2D>;
};

template<>
struct IntersectionResultTypes<LineSegment2D, LineSegment2D> {
  using types = boost::variant<Point2D, LineSegment2D>;
};

std::vector<IntersectionTypes<LineSegment2D, LineSegment2D>> intersections(const LineSegment2D&, const LineSegment2D&);
std::vector<IntersectionTypes<LineSegment2D, Line2D>> intersections(const LineSegment2D&, const Line2D&);
std::vector<IntersectionTypes<Line2D, LineSegment2D>> intersections(const Line2D&, const LineSegment2D&);
std::vector<IntersectionTypes<LineSegment2D, Ray2D>> intersections(const LineSegment2D&, const Ray2D&);
std::vector<IntersectionTypes<Ray2D, LineSegment2D>> intersections(const Ray2D&, const LineSegment2D&);


// Polygon2D
template<>
struct IntersectionResultTypes<Polygon2D, Line2D> {
  using types = boost::variant<Point2D, LineSegment2D>;
};

template<>
struct IntersectionResultTypes<Polygon2D, Ray2D> {
  using types = boost::variant<Point2D, LineSegment2D>;
};

template<>
struct IntersectionResultTypes<Polygon2D, LineSegment2D> {
  using types = boost::variant<Point2D, LineSegment2D>;
};

template<>
struct IntersectionResultTypes<Polygon2D, Polygon2D> {
  using types = boost::variant<Point2D, LineSegment2D>;
};

std::vector<IntersectionTypes<Polygon2D, Polygon2D>> intersections(const Polygon2D&, const Polygon2D&);
std::vector<IntersectionTypes<Polygon2D, Line2D>> intersections(const Polygon2D&, const Line2D&);
std::vector<IntersectionTypes<Line2D, Polygon2D>> intersections(const Line2D&, const Polygon2D&);
std::vector<IntersectionTypes<Polygon2D, Ray2D>> intersections(const Polygon2D&, const Ray2D&);
std::vector<IntersectionTypes<Ray2D, Polygon2D>> intersections(const Ray2D&, const Polygon2D&);
std::vector<IntersectionTypes<Polygon2D, LineSegment2D>> intersections(const Polygon2D&, const LineSegment2D&);
std::vector<IntersectionTypes<LineSegment2D, Polygon2D>> intersections(const LineSegment2D&, const Polygon2D&);


} // namespace wigeon
