#include "wigeon/intersections.h"

#include <cmath>
#include <limits>

#include "wigeon/printer.h"
#include <iostream>
using namespace std;

namespace wigeon {

bool curves_intersect(const Vector2D& v, const Vector2D& w0, const Vector2D& w1) {
  double n0 = cross(w0, v);
  double n1 = cross(w1, v);

  // Case 1a: clean intersection through corner
  if (n0*n1 < 0) {
    return true;
  }

  // Case 1b: Both segments are on the same side of the Line
  if (n0*n1 > 0) {
    return false;
  }

  // Case 1c: Both segments are on the line
  if (n0==0 && n1==0) {
    return false;
  }

  // Case 1d: Anti-Clockwise touching intersection
  if (n0>0 || n1>0) {
    return true;
  }

  // Case 1d: Clockwise touching intersection
  return false;
}

// bool curves_intersect(const Vector2D& v0, const Vector2D& v1, const Vector2D& w0, const Vector2D& w1) {
// }

Points2D intersections(const Line2D& line0, const Line2D& line1) {
  const Vector2D& u0 = line0.direction();
  const Vector2D& u1 = line1.direction();

  // Return no intersection points if u0 and u1 are exactly parallel
  double a = u0*u1;
  if (a*a == 1)
    return Points2D();

  const Point2D& p0 = line0.point();
  const Point2D& p1 = line1.point();

  double c0 = (p1-p0) * (u0 - u1*(u0*u1)) / (1-a*a);

  Points2D points;
  points.push_back(p0 + u0*c0);
  return points;
}

Points2D intersections(const Line2D& line, const Ray2D& ray) {
  const Vector2D& u0 = line.direction();
  const Vector2D& u1 = ray.direction();

  // Return no intersection points if u0 and u1 are exactly parallel
  double a = u0*u1;
  if (a*a==1)
    return Points2D();

  // Check if line and ray are intersecting
  const Point2D& p0 = line.point();
  const Point2D& p1 = ray.point();

  Vector2D w = p0 - p1;
  Vector2D n = normalvector(u0);

  if ((n*w)*(n*u1) <= 0)
    return Points2D();

  double c1 = (p0-p1) * (u1 - u0*(u1*u0)) / (1-a*a);

  Points2D points;
  points.push_back(p1 + u1*c1);
  return points;
}

Points2D intersections(const Ray2D& ray, const Line2D& line) {
  return intersections(line, ray);
}

Points2D intersections(const Ray2D& ray, const LineSegment2D& segment) {
  // Check if segment points are on different sides of the ray
  double n0 = cross(ray.direction(), segment.point0()-ray.point());
  double n1 = cross(ray.direction(), segment.point1()-ray.point());

  if (n0*n1 >= 0) {
    return Points2D();
  }

  // Segment points are on different sides
  return intersections(ray, Line2D(segment));
}

Points2D intersections(const LineSegment2D& segment, const Ray2D& ray) {
  return intersections(ray, segment);
}

Points2D intersections(const Line2D& line, const LineSegment2D& segment) {
  // Check if segment points are on different sides of the line
  double n0 = cross(line.direction(), segment.point0()-line.point());
  double n1 = cross(line.direction(), segment.point1()-line.point());

  if (n0*n1 >= 0) {
    return Points2D();
  }

  // Segment points are on different sides
  return intersections(line, Line2D(segment));
}

Points2D intersections(const LineSegment2D& segment, const Line2D& line) {
  return intersections(line, segment);
}

Points2D intersections(const LineSegment2D& segment0, const LineSegment2D& segment1) {
  // Check if segment1 points are on different sides of segment0
  Vector2D v0 = segment0.point1() - segment0.point0();
  double n0 = cross(v0, segment1.point0()-segment0.point0());
  double n1 = cross(v0, segment1.point1()-segment0.point0());
  if (n0*n1>=0)
    return Points2D();

  // Check if segment0 points are on different sides of segment1
  Vector2D v1 = segment1.point1() - segment1.point0();
  n0 = cross(v1, segment0.point0()-segment1.point0());
  n1 = cross(v1, segment0.point1()-segment1.point0());
  if (n0*n1>=0)
    return Points2D();
  
  // Segments are intersecting
  return intersections(Line2D(segment0), Line2D(segment1));
}

// DoubleLineSegment2D
Points2D intersections(const DoubleLineSegment2D& dsegment, const Line2D& line) {
  Points2D points;

  // Case 1: corner point is intersected
  Vector2D w1 = dsegment.point1() - line.point();
  if (cross(w1, line.direction()) == 0) {
    Vector2D w0 = dsegment.point0() - line.point();
    Vector2D w2 = dsegment.point2() - line.point();
    if (curves_intersect(line.direction(), w0, w2)) {
      points.push_back(dsegment.point1());
    }
    return points;
  }

  // Case 2: corner point is not intersected
  Points2D subpoints0 = intersections(dsegment.segment0(), line);
  if (subpoints0.size()==1) {
    points.push_back(subpoints0.front());
  }
  Points2D subpoints1 = intersections(dsegment.segment1(), line);
  if (subpoints1.size()==1) {
    points.push_back(subpoints1.front());
  }
  return points;
}

Points2D intersections(const Line2D& line, const DoubleLineSegment2D& dsegment) {
  return intersections(dsegment, line);
}

Points2D intersections(const DoubleLineSegment2D& dsegment, const Ray2D& ray) {
  Points2D points;

  // Case 1: corner point is intersected
  Vector2D w1 = dsegment.point1() - ray.point();
  if (cross(w1, ray.direction()) == 0) {
    // Direction of the ray is away from point
    if (w1*ray.direction()<=0) {
      return points;
    }
    Vector2D w0 = dsegment.point0() - ray.point();
    Vector2D w2 = dsegment.point2() - ray.point();
    if (curves_intersect(ray.direction(), w0, w2)) {
      points.push_back(dsegment.point1());
    }
    return points;
  }

  // Case 2: corner point is not intersected
  Points2D subpoints0 = intersections(dsegment.segment0(), ray);
  if (subpoints0.size()==1) {
    points.push_back(subpoints0.front());
  }
  Points2D subpoints1 = intersections(dsegment.segment1(), ray);
  if (subpoints1.size()==1) {
    points.push_back(subpoints1.front());
  }
  return points;
}

Points2D intersections(const Ray2D& ray, const DoubleLineSegment2D& dsegment) {
  return intersections(dsegment, ray);
}


Points2D intersections(const Ray2D& ray, const Polygon2D& polygon) {
  // Handle special cases
  int size = polygon.size();
  switch (size) {
    case 0: return Points2D();
    case 1: return Points2D();
  }

  Points2D points;
  Points2D subpoints;
  for (int i=0; i<polygon.size(); ++i) {
    subpoints = intersections(ray, *polygon.edge(i));
    // Case 1: Segment is intersected cleanly
    if (subpoints.size()==1) {
      points.push_back(subpoints[0]);
      continue;
    }

    // Case 2: Neither the current segment nor the current point are intersected
    Vector2D w = *polygon.point(i)-ray.point();
    if (cross(ray.direction(), w) != 0 || ray.direction()*w<=0)
      continue;

    // Case 3: Point is intersected
    double n0 = cross(ray.direction(), *polygon.point_looped(i-1) - ray.point());
    double n1 = cross(ray.direction(), *polygon.point_looped(i+1) - ray.point());

    // Case 3a: The adjacent points are on different sides of the ray
    if (n0*n1 < 0) {
      points.push_back(*polygon.point(i));
      continue;
    }
    
    // Case 3b: The adjacent points are on the same side of the ray
    if (n0*n1 > 0)
      continue;
    
    // Case 3c: The adjacent segments are both on the ray
    if (n0==0 && n1==0)
      continue;

    // Case 3d: One of the adjacent points is not on the line and turns in
    // positive direction.
    if (n0>0 || n1>0)
      points.push_back(*polygon.point(i));
  }
  return points;
}

Points2D intersections(const Polygon2D& polygon, const Ray2D& ray) {
  return intersections(ray, polygon);
}


Points2D intersections(const LineSegment2D& segment, const Polygon2D& polygon) {
  // Handle special cases
  int size = polygon.size();
  switch (size) {
    case 0: return Points2D();
    case 1: return Points2D();
  }
  if (size==2) {
    Points2D points = intersections(segment, *polygon.edge(0));
    if (points.size()==0) {
      points.push_back(points[0]);
    }
    return points;
  }

  Points2D points;
  Points2D subpoints;
  for (int i=0; i<polygon.size(); ++i) {
    subpoints = intersections(segment, *polygon.edge(i));
    // Case 1: Segment is intersected cleanly
    if (subpoints.size()==1) {
      points.push_back(subpoints[0]);
      continue;
    }

    // Case 2: Neither the current segment nor the current point are intersected
    Vector2D v = segment.point1() - segment.point0();
    Vector2D w = *polygon.point(i) - segment.point0();
    if (cross(v, w) != 0 || v*w <= 0 || v*w >= w*w)
      continue;
 
    // Case 3: Point is intersected
    double n0 = cross(v, *polygon.point_looped(i-1) - segment.point0());
    double n1 = cross(v, *polygon.point_looped(i+1) - segment.point0());

    // Case 3a: The adjacent points are on different sides of the segment
    if (n0*n1 < 0) {
      points.push_back(*polygon.point(i));
      continue;
    }
    
    // Case 3b: The adjacent points are on the same side of the segment
    if (n0*n1 > 0)
      continue;
    
    // Case 3c: The adjacent segments are both on the ray
    if (n0==0 && n1==0)
      continue;

    // Case 3d: One of the adjacent points is not on the line and turns in
    // positive direction.
    if (n0>0 || n1>0)
      points.push_back(*polygon.point(i));
  }
  return points;
}


Points2D intersections(const Polygon2D& polygon0, const Polygon2D& polygon1) {
  Points2D points;
  Points2D points_part;
  for (int i=0; i<polygon0.size(); ++i) {
    points_part = intersections(*polygon0.edge(i), polygon1);
    if (points_part.size() > 0) {
      points.insert(points.end(), points_part.begin(), points_part.end());
    }
  }
  return points;
}

} // namespace wigeon
