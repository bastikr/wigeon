#include "wigeon/intersections.h"

#include <cmath>


namespace wigeon {

std::vector<IntersectionTypes<Line2D, Line2D>> intersections(const Line2D& line0, const Line2D& line1) {
  std::vector<IntersectionTypes<Line2D, Line2D>> results;
  double a = cross(line0.direction(), line1.direction());
  // Lines parallel
  if (a==0) {
    if (cross(line0.direction(), line1.point() - line0.point())==0) {
      IntersectionDescription<Line2D, Line2D> description;
      Intersection<Line2D, Line2D, Line2D> intersection(line0, description, description);
      results.push_back(intersection);
    }
    return results;
  }

  // Lines are intersecting
  double n0 = cross(line0.point() - Point2D(0, 0), line0.direction());
  double n1 = cross(line1.point() - Point2D(0, 0), line1.direction());
  Point2D x = Point2D(0, 0) + n1/a*line0.direction() - n0/a*line1.direction();

  double s0 = (x - line0.point())*line0.direction();
  double s1 = (x - line1.point())*line1.direction();

  IntersectionDescription<Line2D, Point2D> description0(s0);
  IntersectionDescription<Line2D, Point2D> description1(s1);
  Intersection<Line2D, Line2D, Point2D> intersection(x, description0, description1);
  results.push_back(intersection);

  return results;
}


std::vector<IntersectionTypes<Ray2D, Line2D>> intersections(const Ray2D& ray, const Line2D& line) {
  std::vector<IntersectionTypes<Ray2D, Line2D>> results;

  Vector2D u_line_ray = ray.point() - line.point();
  double c0 = cross(line.direction(), u_line_ray);
  double c1 = cross(line.direction(), ray.direction());

  // No intersection
  if ((c0>0 && c1>=0) || (c0<0 && c1<=0)) {
    return results;
  }

  // Parallel and intersecting
  if (c0==0 && c1==0) {
    IntersectionDescription<Ray2D, Ray2D> description0(0);
    double r_line = line.direction()*u_line_ray;
    bool direction = (line.direction()*ray.direction() > 0);
    IntersectionDescription<Line2D, Ray2D> description1(r_line, direction);
    Intersection<Ray2D, Line2D, Ray2D> intersection(ray, description0, description1);
    results.push_back(intersection);
    return results;
  }

  // Non-parallel, ray starting point is on the line
  // if (c0==0 && c1!=0) {
  //   IntersectionDescription<Ray2D, Point2D> description0(0);
  //   double r_line = line.direction()*u_line_ray;
  //   IntersectionDescription<Line2D, Point2D> description1(r_line);
  //   Intersection<Ray2D, Line2D, Point2D> intersection(ray.point(), description0, description1);
  //   results.push_back(intersection);
  //   return results;
  // }

  // Clean intersection
  double n0 = cross(ray.point() - Point2D(0, 0), ray.direction());
  double n1 = cross(line.point() - Point2D(0, 0), line.direction());
  double a = -c1;
  Point2D x = Point2D(0, 0) + n1/a*ray.direction() - n0/a*line.direction();

  double r0 = (x - ray.point())*ray.direction();
  double r1 = (x - line.point())*line.direction();

  IntersectionDescription<Ray2D, Point2D> description0(r0);
  IntersectionDescription<Line2D, Point2D> description1(r1);
  Intersection<Ray2D, Line2D, Point2D> intersection(x, description0, description1);
  results.push_back(intersection);

  return results;
}

std::vector<IntersectionTypes<Line2D, Ray2D>> intersections(const Line2D& line, const Ray2D& ray) {
  std::vector<IntersectionTypes<Ray2D, Line2D>> results = intersections(ray, line);
  std::vector<IntersectionTypes<Line2D, Ray2D>> results_flipped;
  flip_visitor<Ray2D, Line2D> visitor; 
  for (auto& r: results)
    results_flipped.push_back(r.apply_visitor(visitor));
  return results_flipped;
}


std::vector<IntersectionTypes<Ray2D, Ray2D>> intersections(const Ray2D& ray0, const Ray2D& ray1) {
  std::vector<IntersectionTypes<Ray2D, Ray2D>> results;

  Vector2D v01 = ray1.point() - ray0.point();
  double c0 = cross(ray0.direction(), v01);
  double c1 = cross(ray1.direction(), v01);
  double c01 = cross(ray0.direction(), ray1.direction());

  // No intersection
  if ((c01>=0 && (c0>0 || c1>0))
    ||(c01<=0 && (c0<0 || c1<0))) {
    return results;
  }

  // Parallel and on same line
  if (c01==0 && c1==0) {
    double r = ray0.direction()*v01;
    // Same direction
    if (ray0.direction()*ray1.direction()>0) {
      // Second ray is completely on first ray
      if (r>=0) {
        IntersectionDescription<Ray2D, Ray2D> description0(r);
        IntersectionDescription<Ray2D, Ray2D> description1(0);
        Intersection<Ray2D, Ray2D, Ray2D> intersection(ray1, description0, description1);
        results.push_back(intersection);
        return results;
      } else { // First ray is completely on second ray
        IntersectionDescription<Ray2D, Ray2D> description0(0);
        IntersectionDescription<Ray2D, Ray2D> description1(-r);
        Intersection<Ray2D, Ray2D, Ray2D> intersection(ray0, description0, description1);
        results.push_back(intersection);
        return results;
      }
    }
    // Opposite direction
    if (r==0) {
      IntersectionDescription<Ray2D, Point2D> description0(0);
      IntersectionDescription<Ray2D, Point2D> description1(0);
      Intersection<Ray2D, Ray2D, Point2D> intersection(ray0.point(), description0, description1);
      results.push_back(intersection);
      return results;
    } else if (r>0) {
      IntersectionDescription<Ray2D, LineSegment2D> description0(0, r);
      IntersectionDescription<Ray2D, LineSegment2D> description1(0, r);
      LineSegment2D segment(ray0.point(), ray1.point());
      Intersection<Ray2D, Ray2D, LineSegment2D> intersection(segment, description0, description1);
      results.push_back(intersection);
      return results;
    } else {
      return results;
    }
  }

  // Clean intersection
  double n0 = cross(ray0.point() - Point2D(0, 0), ray0.direction());
  double n1 = cross(ray1.point() - Point2D(0, 0), ray1.direction());
  double a = c01;
  Point2D x = Point2D(0, 0) + n1/a*ray0.direction() - n0/a*ray1.direction();

  double r0 = (x - ray0.point())*ray0.direction();
  double r1 = (x - ray1.point())*ray1.direction();

  IntersectionDescription<Ray2D, Point2D> description0(r0);
  IntersectionDescription<Ray2D, Point2D> description1(r1);
  Intersection<Ray2D, Ray2D, Point2D> intersection(x, description0, description1);
  results.push_back(intersection);

  return results;
}


std::vector<IntersectionTypes<LineSegment2D, Line2D>> intersections(const LineSegment2D& segment, const Line2D& line) {
  std::vector<IntersectionTypes<LineSegment2D, Line2D>> results;

  Vector2D v0 = segment.point0() - line.point();
  Vector2D v1 = segment.point1() - line.point();
  double c0 = cross(line.direction(), v0);
  double c1 = cross(line.direction(), v1);

  // No intersection
  if ((c0>0 && c1>0) || (c0<0 && c1<0)) {
    return results;
  }

  // Segment is completely on line
  if (c0==0 && c1==0) {
    IntersectionDescription<LineSegment2D, LineSegment2D> description0(0, 1);
    double r0 = line.direction()*v0;
    double r1 = line.direction()*v1;
    IntersectionDescription<Line2D, LineSegment2D> description1(r0, r1);
    Intersection<LineSegment2D, Line2D, LineSegment2D> intersection(segment, description0, description1);
    results.push_back(intersection);
    return results;
  }

  // First point of segment is on line
  if (c0==0) {
    IntersectionDescription<LineSegment2D, Point2D> description0(0);
    double r0 = line.direction()*v0;
    IntersectionDescription<Line2D, Point2D> description1(r0);
    Intersection<LineSegment2D, Line2D, Point2D> intersection(segment.point0(), description0, description1);
    results.push_back(intersection);
    return results;
  }

  // Second point of segment on line
  if (c1==0) {
    IntersectionDescription<LineSegment2D, Point2D> description0(1);
    double r1 = line.direction()*v1;
    IntersectionDescription<Line2D, Point2D> description1(r1);
    Intersection<LineSegment2D, Line2D, Point2D> intersection(segment.point1(), description0, description1);
    results.push_back(intersection);
    return results;
  }

  // Clean intersection
  Point2D p0 = segment.point0();
  Point2D p1 = segment.point1();

  Vector2D segmentvector = p1 - p0;
  double a = cross(segmentvector, line.direction());

  double n0 = p0.x()*p1.y() - p0.y()*p1.x();
  double n1 = cross(line.point() - Point2D(0, 0), line.direction());

  Point2D x = Point2D(0, 0) + n1/a*segmentvector - n0/a*line.direction();

  double r0 = (x - p0)*segmentvector/segmentvector.length2();
  double r1 = (x - line.point())*line.direction();

  IntersectionDescription<LineSegment2D, Point2D> description0(r0);
  IntersectionDescription<Line2D, Point2D> description1(r1);
  Intersection<LineSegment2D, Line2D, Point2D> intersection(x, description0, description1);
  results.push_back(intersection);

  return results;
}

std::vector<IntersectionTypes<Line2D, LineSegment2D>> intersections(const Line2D& line, const LineSegment2D& ray) {
  std::vector<IntersectionTypes<LineSegment2D, Line2D>> results = intersections(ray, line);
  std::vector<IntersectionTypes<Line2D, LineSegment2D>> results_flipped;
  flip_visitor<LineSegment2D, Line2D> visitor; 
  for (auto& r: results)
    results_flipped.push_back(r.apply_visitor(visitor));
  return results_flipped;
}


std::vector<IntersectionTypes<LineSegment2D, Ray2D>> intersections(const LineSegment2D& segment, const Ray2D& ray) {
  std::vector<IntersectionTypes<LineSegment2D, Ray2D>> results;

  Vector2D v0 = segment.point0() - ray.point();
  Vector2D v1 = segment.point1() - ray.point();
  double c_r0 = cross(ray.direction(), v0);
  double c_r1 = cross(ray.direction(), v1);

  // No intersection, both segment points are on the same side of the ray
  if ((c_r0>0 && c_r1>0) || (c_r0<0 && c_r1<0)) {
    return results;
  }

  Vector2D vs = segment.point1() - segment.point0();
  double c_sp = cross(vs, v0);
  double c_sd = cross(vs, ray.direction());

  // No intersection, ray is facing away from segment
  if ((c_sp>0 && c_sd<0) || (c_sp<0 && c_sd>0)) {
    return results;
  }

  double p_r0 = ray.direction()*v0;
  double p_r1 = ray.direction()*v1;

  // No intersection, segment is directly behind the ray
  if (p_r0<0 && p_r1<0) {
    return results;
  }

  // Segment is completely on the rays baseline and at least a segment part intersects the ray
  if (c_r0==0 && c_r1==0 && (p_r0>0 || p_r1>0)) {
    double s0 = 0;
    double s1 = 1;
    Point2D p0 = segment.point0();
    Point2D p1 = segment.point1();
    if (p_r0<0) {
      p_r0 = 0;
      s0 = v0.length()/vs.length();
      p0 = ray.point();
    }
    if (p_r1<0) {
      p_r1 = 0;
      s1 = 1-v1.length()/vs.length();
      p1 = ray.point();
    }
    LineSegment2D result_segment(p0, p1);
    IntersectionDescription<LineSegment2D, LineSegment2D> description0(s0, s1);
    IntersectionDescription<Ray2D, LineSegment2D> description1(p_r0, p_r1);
    Intersection<LineSegment2D, Ray2D, LineSegment2D> intersection(result_segment, description0, description1);
    results.push_back(intersection);
    return results;
  }

  // First point of segment is on ray
  if (c_r0==0 && p_r0>=0) {
    IntersectionDescription<LineSegment2D, Point2D> description0(0);
    IntersectionDescription<Ray2D, Point2D> description1(p_r0);
    Intersection<LineSegment2D, Ray2D, Point2D> intersection(segment.point0(), description0, description1);
    results.push_back(intersection);
    return results;
  }

  // Second point of segment on ray
  if (c_r1==0 && p_r1>=0) {
    IntersectionDescription<LineSegment2D, Point2D> description0(1);
    IntersectionDescription<Ray2D, Point2D> description1(p_r1);
    Intersection<LineSegment2D, Ray2D, Point2D> intersection(segment.point1(), description0, description1);
    results.push_back(intersection);
    return results;
  }

  // Clean intersection
  Point2D p0 = segment.point0();
  Point2D p1 = segment.point1();

  Vector2D segmentvector = p1 - p0;
  double a = cross(segmentvector, ray.direction());

  double n0 = p0.x()*p1.y() - p0.y()*p1.x();
  double n1 = cross(ray.point() - Point2D(0, 0), ray.direction());

  Point2D x = Point2D(0, 0) + n1/a*segmentvector - n0/a*ray.direction();

  double r0 = (x - p0)*segmentvector/segmentvector.length2();
  double r1 = (x - ray.point())*ray.direction();

  IntersectionDescription<LineSegment2D, Point2D> description0(r0);
  IntersectionDescription<Ray2D, Point2D> description1(r1);
  Intersection<LineSegment2D, Ray2D, Point2D> intersection(x, description0, description1);
  results.push_back(intersection);

  return results;
}

std::vector<IntersectionTypes<Ray2D, LineSegment2D>> intersections(const Ray2D& ray, const LineSegment2D& segment) {
  std::vector<IntersectionTypes<LineSegment2D, Ray2D>> results = intersections(segment, ray);
  std::vector<IntersectionTypes<Ray2D, LineSegment2D>> results_flipped;
  flip_visitor<LineSegment2D, Ray2D> visitor; 
  for (auto& r: results)
    results_flipped.push_back(r.apply_visitor(visitor));
  return results_flipped;
}


std::vector<IntersectionTypes<LineSegment2D, LineSegment2D>> intersections(const LineSegment2D& segment0, const LineSegment2D& segment1) {
  std::vector<IntersectionTypes<LineSegment2D, LineSegment2D>> results;

  Vector2D v01 = segment0.point1() - segment0.point0();
  Vector2D v02 = segment1.point0() - segment0.point0();
  Vector2D v03 = segment1.point1() - segment0.point0();

  double c01_02 = cross(v01, v02);
  double c01_03 = cross(v01, v03);

  // No intersection, both segment1 points are on the same side in regard to segment0
  if ((c01_02>0 && c01_03>0) || (c01_02<0 && c01_03<0)) {
    return results;
  }

  Vector2D v23 = segment1.point1() - segment1.point0();
  Vector2D v20 = segment0.point0() - segment1.point0();
  Vector2D v21 = segment0.point1() - segment1.point0();
  
  double c23_20 = cross(v23, v20);
  double c23_21 = cross(v23, v21);

  // No intersection, both segment0 points are on the same side in regard to segment1
  if ((c23_20>0 && c23_21>0) || (c23_20<0 && c23_21<0)) {
    return results;
  }

  Point2D p0 = segment0.point0();
  Point2D p1 = segment0.point1();
  Point2D p2 = segment1.point0();
  Point2D p3 = segment1.point1();

  // Line segments parallel and on the same line
  if (c01_02==0 && c01_03==0) {
    double d02 = v01*v02;
    double d03 = v01*v03;
    double d12 = -v01*v21;
    double d13 = v01*(segment1.point1() - segment0.point1());

    // No intersection
    if ((d02<0 && d03<0) || (d12>0 && d13>0))
      return results; 

    // Only edge points are intersecting
    if (d02==0 && d03<=0) {
      IntersectionDescription<LineSegment2D, Point2D> description0(0);
      IntersectionDescription<LineSegment2D, Point2D> description1(0);
      Intersection<LineSegment2D, LineSegment2D, Point2D> intersection(segment0.point0(), description0, description1);
      results.push_back(intersection);
      return results;
    }
    if (d03==0 && d02<=0) {
      IntersectionDescription<LineSegment2D, Point2D> description0(0);
      IntersectionDescription<LineSegment2D, Point2D> description1(1);
      Intersection<LineSegment2D, LineSegment2D, Point2D> intersection(segment0.point0(), description0, description1);
      results.push_back(intersection);
      return results;
    }

    if (d12==0 && d13>=0) {
      IntersectionDescription<LineSegment2D, Point2D> description0(1);
      IntersectionDescription<LineSegment2D, Point2D> description1(0);
      Intersection<LineSegment2D, LineSegment2D, Point2D> intersection(segment0.point1(), description0, description1);
      results.push_back(intersection);
      return results;
    }
    if (d13==0 && d12>=0) {
      IntersectionDescription<LineSegment2D, Point2D> description0(1);
      IntersectionDescription<LineSegment2D, Point2D> description1(1);
      Intersection<LineSegment2D, LineSegment2D, Point2D> intersection(segment0.point1(), description0, description1);
      results.push_back(intersection);
      return results;
    }

    // Parts of the segments intersect
    double r0_0 = 0;
    double r0_1 = 1;
    double r1_0 = 0;
    double r1_1 = 1;
    if (d02<d03) {
      if (d02>0) {
        p0 = segment1.point0();
        r0_0 = d02/v01.length2();
        r1_0 = 0;
      } else if (d02<0) {
        r0_0 = 0;
        r1_0 = -d02/v01.length()/v23.length();
      }
      if (d13<0) {
        p1 = segment1.point1();
        r0_1 = d03/v01.length2();
        r1_1 = 1;
      } else if (d13>0) {
        r0_1 = 1;
        r1_1 = -d12/v01.length()/v23.length();
      }
    } else {
      if (d03>0) {
        p0 = segment1.point1();
        r0_0 = d03/v01.length2();
        r1_0 = 1;
      } else if (d03<0) {
        r0_0 = 0;
        r1_0 = d02/v01.length()/v23.length();
      }
      if (d12<0) {
        p1 = segment1.point0();
        r0_1 = d02/v01.length2();
        r1_1 = 0;
      } else if (d12>0) {
        r0_1 = 1;
        r1_1 = d12/v01.length()/v23.length();
      }
    }

    IntersectionDescription<LineSegment2D, LineSegment2D> description0(r0_0, r0_1);
    IntersectionDescription<LineSegment2D, LineSegment2D> description1(r1_0, r1_1);
    Intersection<LineSegment2D, LineSegment2D, LineSegment2D> intersection(LineSegment2D(p0, p1), description0, description1);
    results.push_back(intersection);
    return results;
  }

  // Clean intersection
  double a = cross(v01, v23);
  double c01 = p0.x()*p1.y() - p0.y()*p1.x();
  double c23 = p2.x()*p3.y() - p2.y()*p3.x();

  Point2D x = Point2D(0, 0) - c01/a*v23 + c23/a*v01;

  double r0 = (x - p0)*v01/v01.length2();
  double r1 = (x - p2)*v23/v23.length2();

  IntersectionDescription<LineSegment2D, Point2D> description0(r0);
  IntersectionDescription<LineSegment2D, Point2D> description1(r1);
  Intersection<LineSegment2D, LineSegment2D, Point2D> intersection(x, description0, description1);
  results.push_back(intersection);
  return results;
}


namespace {

template <typename T0>
class polygonintersection_visitor : public boost::static_visitor<IntersectionTypes<T0, Polygon2D>> {
  public:
    explicit polygonintersection_visitor(size_t index) : index(index) {}

    template <typename T>
    IntersectionTypes<T0, Polygon2D> operator()(const T& object) {
      using ResultType = typename T::ResultType;
      IntersectionDescription<Polygon2D, ResultType> d1(index, object.description1);
      return Intersection<T0, Polygon2D, ResultType>(object.result, object.description0, d1);
    }

    size_t index;
};

} // anonymous namespace


std::vector<IntersectionTypes<Line2D, Polygon2D>> intersections(const Line2D& line, const Polygon2D& polygon) {
  std::vector<IntersectionTypes<Line2D, Polygon2D>> results;
  std::vector<IntersectionTypes<Line2D, LineSegment2D>> subresults;
  polygonintersection_visitor<Line2D> visitor(0);
  for (size_t i=0; i<polygon.size(); ++i) {
    subresults = intersections(line, polygon.edge(i));
    for (const auto& result: subresults) {
      visitor.index = i;
      results.push_back(result.apply_visitor(visitor));
    }
  }
  return results;
}

std::vector<IntersectionTypes<Polygon2D, Line2D>> intersections(const Polygon2D& polygon, const Line2D& line) {
  std::vector<IntersectionTypes<Line2D, Polygon2D>> results = intersections(line, polygon);
  std::vector<IntersectionTypes<Polygon2D, Line2D>> results_flipped;
  flip_visitor<Line2D, Polygon2D> visitor; 
  for (auto& r: results)
    results_flipped.push_back(r.apply_visitor(visitor));
  return results_flipped;
}


std::vector<IntersectionTypes<Ray2D, Polygon2D>> intersections(const Ray2D& ray, const Polygon2D& polygon) {
  std::vector<IntersectionTypes<Ray2D, Polygon2D>> results;
  std::vector<IntersectionTypes<Ray2D, LineSegment2D>> subresults;
  polygonintersection_visitor<Ray2D> visitor(0);
  for (size_t i=0; i<polygon.size(); ++i) {
    subresults = intersections(ray, polygon.edge(i));
    for (const auto& result: subresults) {
      visitor.index = i;
      results.push_back(result.apply_visitor(visitor));
    }
  }
  return results;
}

std::vector<IntersectionTypes<Polygon2D, Ray2D>> intersections(const Polygon2D& polygon, const Ray2D& ray) {
  std::vector<IntersectionTypes<Ray2D, Polygon2D>> results = intersections(ray, polygon);
  std::vector<IntersectionTypes<Polygon2D, Ray2D>> results_flipped;
  flip_visitor<Ray2D, Polygon2D> visitor; 
  for (auto& r: results)
    results_flipped.push_back(r.apply_visitor(visitor));
  return results_flipped;
}


std::vector<IntersectionTypes<LineSegment2D, Polygon2D>> intersections(const LineSegment2D& segment, const Polygon2D& polygon) {
  std::vector<IntersectionTypes<LineSegment2D, Polygon2D>> results;
  std::vector<IntersectionTypes<LineSegment2D, LineSegment2D>> subresults;
  polygonintersection_visitor<LineSegment2D> visitor(0);
  for (size_t i=0; i<polygon.size(); ++i) {
    subresults = intersections(segment, polygon.edge(i));
    for (const auto& result: subresults) {
      visitor.index = i;
      results.push_back(result.apply_visitor(visitor));
    }
  }
  return results;
}

std::vector<IntersectionTypes<Polygon2D, LineSegment2D>> intersections(const Polygon2D& polygon, const LineSegment2D& segment) {
  std::vector<IntersectionTypes<LineSegment2D, Polygon2D>> results = intersections(segment, polygon);
  std::vector<IntersectionTypes<Polygon2D, LineSegment2D>> results_flipped;
  flip_visitor<LineSegment2D, Polygon2D> visitor; 
  for (auto& r: results)
    results_flipped.push_back(r.apply_visitor(visitor));
  return results_flipped;
}


std::vector<IntersectionTypes<Polygon2D, Polygon2D>> intersections(const Polygon2D& polygon0, const Polygon2D& polygon1) {
  std::vector<IntersectionTypes<Polygon2D, Polygon2D>> results;
  std::vector<IntersectionTypes<Polygon2D, LineSegment2D>> subresults;
  polygonintersection_visitor<Polygon2D> visitor(0);
  for (size_t i=0; i<polygon1.size(); ++i) {
    subresults = intersections(polygon0, polygon1.edge(i));
    for (const auto& result: subresults) {
      visitor.index = i;
      results.push_back(result.apply_visitor(visitor));
    }
  }
  return results;
}

} // namespace wigeon
