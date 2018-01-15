#include "wigeon/intersections.h"

#include <cmath>
#include <limits>


namespace wigeon {

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
  const Point2D& p0 = line.point();
  const Vector2D& u0 = line.direction();

  const Point2D& p1 = ray.point();
  const Vector2D& u1 = ray.direction();
  
  Vector2D w = p1 - p0;

  // Check if line and ray are intersecting
  Points2D points;
  if (u1*w >= 0)
    return points;

  // Calculate intersection point
  double a = u1*u0;
  double c1 = (p0-p1) * (u1 - u0*(u1*u0)) / (1-a*a);

  // Return no intersection points If u0 and u1 are exactly parallel
  if (std::isnan(c1) || std::isinf(c1) || c1 <= 0)
    return points;
  
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

Points2D intersections(const LineSegment2D& segment0, const LineSegment2D& segment1) {
  Vector2D v0 = segment0.point1() - segment0.point0();
  Vector2D v1 = segment1.point1() - segment1.point0();
  Vector2D w = segment1.point0() - segment0.point1();

  // Check if segment1 points are on different sides of segment0
  double n0 = cross(v0, segment1.point0()-segment0.point0());
  double n1 = cross(v0, segment1.point1()-segment0.point0());
  if (n0*n1>=0)
    return Points2D();

  // Check if segment0 points are on different sides of segment1
  n0 = cross(v1, segment0.point0()-segment1.point1());
  n1 = cross(v1, segment0.point1()-segment1.point0());
  if (n0*n1>=0)
    return Points2D();
  
  // Segments are intersecting
  return intersections(Line2D(segment0), Line2D(segment1));
}


Points2D intersections(const Ray2D& ray, const Polygon2D& polygon) {
  // Handle special cases
  int size = polygon.size();
  switch (size) {
    case 0: return Points2D();
    case 1: return Points2D();
  }
  if (size==2) {
    Points2D points = intersections(ray, *polygon.edge(0));
    if (points.size()==0) {
      points.push_back(points[0]);
    }
    return points;
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
    if (cross(ray.direction(), w) != 0 || ray.direction()*w<0)
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

    // Case 3d: One of the adjacent points is not on the line
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

    // Case 3d: One of the adjacent points is not on the segment
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
