#include "wigeon/crossingpoints.h"

#include <cmath>


namespace wigeon {

namespace {

class intersection_visitor : public boost::static_visitor<std::vector<Point2D>> {
  public:
    std::vector<Point2D> operator()(const Intersection<Line2D, Line2D, Point2D>& object) {
      std::vector<Point2D> points;
      points.push_back(object.result);
      return points;
    }

    std::vector<Point2D> operator()(const Intersection<Line2D, Ray2D, Point2D>& object) {
      std::vector<Point2D> points;
      if (object.description1.r!=0)
        points.push_back(object.result);
      return points;
    }

    std::vector<Point2D> operator()(const Intersection<Ray2D, Ray2D, Point2D>& object) {
      std::vector<Point2D> points;
      if (object.description0.r!=0 && object.description1.r!=0)
        points.push_back(object.result);
      return points;
    }

    std::vector<Point2D> operator()(const Intersection<LineSegment2D, LineSegment2D, Point2D>& object) {
      std::vector<Point2D> points;
      if (object.description0.r!=0 && object.description0.r!=1
          && object.description1.r!=0 && object.description1.r!=1)
        points.push_back(object.result);
      return points;
    }

    std::vector<Point2D> operator()(const Intersection<Line2D, LineSegment2D, Point2D>& object) {
      std::vector<Point2D> points;
      if (object.description1.r!=0 && object.description1.r!=1)
        points.push_back(object.result);
      return points;
    }

    std::vector<Point2D> operator()(const Intersection<Ray2D, LineSegment2D, Point2D>& object) {
      std::vector<Point2D> points;
      if (object.description0.r!=0 && object.description1.r!=0 && object.description1.r!=1)
        points.push_back(object.result);
      return points;
    }

    std::vector<Point2D> operator()(const Intersection<Ray2D, Polygon2D, Point2D>& object) {
      std::vector<Point2D> points;
      if (object.description1.segment.r!=0 && object.description1.segment.r!=1)
        points.push_back(object.result);
      return points;
    }

    std::vector<Point2D> operator()(const Intersection<Line2D, Polygon2D, Point2D>& object) {
      std::vector<Point2D> points;
      if (object.description1.segment.r!=0 && object.description1.segment.r!=1)
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

std::vector<Point2D> crossingpoints(const Ray2D& ray0, const Ray2D& ray1) {
  auto results = intersections(ray0, ray1);
  if (results.size()) {
    intersection_visitor visitor;
    return results.front().apply_visitor(visitor);
  }
  return std::vector<Point2D>();
}

std::vector<Point2D> crossingpoints(const Line2D& line, const Ray2D& ray) {
  auto results = intersections(line, ray);
  if (results.size()==1) {
    intersection_visitor visitor;
    return results.front().apply_visitor(visitor);
  }
  return std::vector<Point2D>();
}

std::vector<Point2D> crossingpoints(const Ray2D& ray, const Line2D& line) {
  return crossingpoints(line, ray);
}


std::vector<Point2D> crossingpoints(const LineSegment2D& segment0, const LineSegment2D& segment1) {
  auto results = intersections(segment0, segment1);
  if (results.size()==1) {
    intersection_visitor visitor;
    return results.front().apply_visitor(visitor);
  }
  return std::vector<Point2D>();
}

std::vector<Point2D> crossingpoints(const Line2D& line, const LineSegment2D& segment) {
  auto results = intersections(line, segment);
  if (results.size()==1) {
    intersection_visitor visitor;
    return results.front().apply_visitor(visitor);
  }
  return std::vector<Point2D>();
}

std::vector<Point2D> crossingpoints(const LineSegment2D& segment, const Line2D& line) {
  return crossingpoints(line, segment);
}

std::vector<Point2D> crossingpoints(const Ray2D& ray, const LineSegment2D& segment) {
  auto results = intersections(ray, segment);
  if (results.size()==1) {
    intersection_visitor visitor;
    return results.front().apply_visitor(visitor);
  }
  return std::vector<Point2D>();
}

std::vector<Point2D> crossingpoints(const LineSegment2D& segment, const Ray2D& ray) {
  return crossingpoints(ray, segment);
}


std::vector<Point2D> crossingpoints(const Line2D& line, const Polygon2D& polygon) {
  auto results = intersections(line, polygon);
  intersection_visitor visitor;
  for (const auto& result: results) {
    return result.apply_visitor(visitor);
  }
  return std::vector<Point2D>();
}

std::vector<Point2D> crossingpoints(const Polygon2D& polygon, const Line2D& line) {
  return crossingpoints(line, polygon);
}

std::vector<Point2D> crossingpoints(const Ray2D& ray, const Polygon2D& polygon) {
  auto results = intersections(ray, polygon);
  intersection_visitor visitor;
  for (const auto& result: results) {
    return result.apply_visitor(visitor);
  }
  return std::vector<Point2D>();
}

std::vector<Point2D> crossingpoints(const Polygon2D& polygon, const Ray2D& ray) {
  return crossingpoints(ray, polygon);
}

} // namespace wigeon
