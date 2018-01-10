#include "wigeon/wigeon.h"
#include "gtest/gtest.h"
#include <cmath>

using namespace wigeon;

TEST(POLYGON2D, OPERATORS) {
  Polygon2D polygon0;
  polygon0.append(0, 0);
  polygon0.append(1, 0);
  polygon0.append(1, 1);

  Vector2D vector(1, 1);

  Polygon2D polygon0_p = polygon0 + vector;
  Point2D p0 = *polygon0_p.point(0);
  Point2D p1 = *polygon0_p.point(1);
  Point2D p2 = *polygon0_p.point(2);
  ASSERT_DOUBLE_EQ(p0.x(), 1);
  ASSERT_DOUBLE_EQ(p0.y(), 1);
  ASSERT_DOUBLE_EQ(p1.x(), 2);
  ASSERT_DOUBLE_EQ(p1.y(), 1);
  ASSERT_DOUBLE_EQ(p2.x(), 2);
  ASSERT_DOUBLE_EQ(p2.y(), 2);

  Polygon2D polygon0_pm = polygon0_p - vector;
  p0 = *polygon0_pm.point(0);
  p1 = *polygon0_pm.point(1);
  p2 = *polygon0_pm.point(2);
  ASSERT_DOUBLE_EQ(p0.x(), 0);
  ASSERT_DOUBLE_EQ(p0.y(), 0);
  ASSERT_DOUBLE_EQ(p1.x(), 1);
  ASSERT_DOUBLE_EQ(p1.y(), 0);
  ASSERT_DOUBLE_EQ(p2.x(), 1);
  ASSERT_DOUBLE_EQ(p2.y(), 1);
}

TEST(POLYGON2D, POINT) {
  Polygon2D polygon0;
  polygon0.append(0, 0);
  polygon0.append(1, 0);
  polygon0.append(0, 1);

  auto point = polygon0.point(0);
  ASSERT_TRUE(bool(point));
  ASSERT_DOUBLE_EQ((*point).x(), 0);
  ASSERT_DOUBLE_EQ((*point).y(), 0);

  point = polygon0.point_looped(0);
  ASSERT_TRUE(bool(point));
  ASSERT_DOUBLE_EQ((*point).x(), 0);
  ASSERT_DOUBLE_EQ((*point).y(), 0);

  point = polygon0.point(2);
  ASSERT_TRUE(bool(point));
  ASSERT_DOUBLE_EQ((*point).x(), 0);
  ASSERT_DOUBLE_EQ((*point).y(), 1);

  point = polygon0.point_looped(2);
  ASSERT_TRUE(bool(point));
  ASSERT_DOUBLE_EQ((*point).x(), 0);
  ASSERT_DOUBLE_EQ((*point).y(), 1);

  point = polygon0.point(3);
  ASSERT_FALSE(bool(point));

  point = polygon0.point_looped(3);
  ASSERT_TRUE(bool(point));
  ASSERT_DOUBLE_EQ((*point).x(), 0);
  ASSERT_DOUBLE_EQ((*point).y(), 0);
}

TEST(POLYGON2D, EDGES) {
  Polygon2D polygon0;
  polygon0.append(0, 0);
  polygon0.append(1, 0);
  polygon0.append(0, 1);

  LineSegment2D s0 = *polygon0.edge(0);
  ASSERT_DOUBLE_EQ(s0.x0(), 0);
  ASSERT_DOUBLE_EQ(s0.y0(), 0);
  ASSERT_DOUBLE_EQ(s0.x1(), 1);
  ASSERT_DOUBLE_EQ(s0.y1(), 0);

  LineSegment2D s0_ = *polygon0.edge_looped(0);
  ASSERT_DOUBLE_EQ(s0_.x0(), 0);
  ASSERT_DOUBLE_EQ(s0_.y0(), 0);
  ASSERT_DOUBLE_EQ(s0_.x1(), 1);
  ASSERT_DOUBLE_EQ(s0_.y1(), 0);

  LineSegment2D s1 = *polygon0.edge(1);
  ASSERT_DOUBLE_EQ(s1.x0(), 1);
  ASSERT_DOUBLE_EQ(s1.y0(), 0);
  ASSERT_DOUBLE_EQ(s1.x1(), 0);
  ASSERT_DOUBLE_EQ(s1.y1(), 1);

  LineSegment2D s1_ = *polygon0.edge_looped(1);
  ASSERT_DOUBLE_EQ(s1_.x0(), 1);
  ASSERT_DOUBLE_EQ(s1_.y0(), 0);
  ASSERT_DOUBLE_EQ(s1_.x1(), 0);
  ASSERT_DOUBLE_EQ(s1_.y1(), 1);

  LineSegment2D s2 = *polygon0.edge(2);
  ASSERT_DOUBLE_EQ(s2.x0(), 0);
  ASSERT_DOUBLE_EQ(s2.y0(), 1);
  ASSERT_DOUBLE_EQ(s2.x1(), 0);
  ASSERT_DOUBLE_EQ(s2.y1(), 0);

  LineSegment2D s2_ = *polygon0.edge_looped(2);
  ASSERT_DOUBLE_EQ(s2_.x0(), 0);
  ASSERT_DOUBLE_EQ(s2_.y0(), 1);
  ASSERT_DOUBLE_EQ(s2_.x1(), 0);
  ASSERT_DOUBLE_EQ(s2_.y1(), 0);

  ASSERT_FALSE(polygon0.edge(-1));

  LineSegment2D sm1_ = *polygon0.edge_looped(-1);
  ASSERT_DOUBLE_EQ(sm1_.x0(), 0);
  ASSERT_DOUBLE_EQ(sm1_.y0(), 1);
  ASSERT_DOUBLE_EQ(sm1_.x1(), 0);
  ASSERT_DOUBLE_EQ(sm1_.y1(), 0);

  ASSERT_FALSE(polygon0.edge(3));

  LineSegment2D s3_ = *polygon0.edge_looped(3);
  ASSERT_DOUBLE_EQ(s3_.x0(), 0);
  ASSERT_DOUBLE_EQ(s3_.y0(), 0);
  ASSERT_DOUBLE_EQ(s3_.x1(), 1);
  ASSERT_DOUBLE_EQ(s3_.y1(), 0);
}
