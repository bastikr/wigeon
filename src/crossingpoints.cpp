#include "wigeon/crossingpoints.h"

#include <cmath>


namespace wigeon {

namespace {

class intersection_visitor : public boost::static_visitor<std::vector<Point2D>> {
  public:
    template <class G0, class G1>
    std::vector<Point2D> operator()(const Intersection<G0, G1, Point2D>& object) {
      std::vector<Point2D> points;
      points.push_back(object.result);
      return points;
    }

    template <class G0, class G1, class Result>
    std::vector<Point2D> operator()(const Intersection<G0, G1, Result>& /*object*/) {
      return std::vector<Point2D>();
    }
};

} // anonymous namespace

std::vector<Point2D> crossingpoints(const Line2D& line0, const Line2D& line1) {
  auto results = intersections(line0, line1);
  if (results.size()==1) {
    intersection_visitor visitor;
    return results.front().apply_visitor(visitor);
  }
  return std::vector<Point2D>();
}

std::vector<Point2D> crossingpoints(const Line2D& line0, const Ray2D& ray) {
  auto results = intersections(line0, ray);
  if (results.size()==1) {
    intersection_visitor visitor;
    return results.front().apply_visitor(visitor);
  }
  return std::vector<Point2D>();
}




} // namespace wigeon
