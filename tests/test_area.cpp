#include "wigeon/area2d.h"
#include "gtest/gtest.h"

#include <cmath>


using namespace wigeon;

TEST(AREA2D, OPERATORS) {
  Area2D area;
  area.exterior_curves.push_back(Circle2D(Point2D(2, 4), 0.5));
  area.interior_curves.push_back(Triangle2D(Point2D(0, 0), Point2D(1, 0), Point2D(0, 1)));
  Area2D area_p = area + Vector2D(1, 2);
  Area2D area_m = area - Vector2D(1, 2);

  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(area_p.exterior_curves.front()).center().x(), 3);
  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(area_p.exterior_curves.front()).center().y(), 6);

  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(area_m.exterior_curves.front()).center().x(), 1);
  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(area_m.exterior_curves.front()).center().y(), 2);

  ASSERT_DOUBLE_EQ(boost::get<Triangle2D>(area_p.interior_curves.front()).point0().x(), 1);
  ASSERT_DOUBLE_EQ(boost::get<Triangle2D>(area_p.interior_curves.front()).point0().y(), 2);

  ASSERT_DOUBLE_EQ(boost::get<Triangle2D>(area_m.interior_curves.front()).point0().x(), -1);
  ASSERT_DOUBLE_EQ(boost::get<Triangle2D>(area_m.interior_curves.front()).point0().y(), -2);


  area_p = Vector2D(1, 2) + area;
  area_m = Vector2D(1, 2) - area;

  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(area_p.exterior_curves.front()).center().x(), 3);
  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(area_p.exterior_curves.front()).center().y(), 6);

  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(area_m.exterior_curves.front()).center().x(), -1);
  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(area_m.exterior_curves.front()).center().y(), -2);

  ASSERT_DOUBLE_EQ(boost::get<Triangle2D>(area_p.interior_curves.front()).point0().x(), 1);
  ASSERT_DOUBLE_EQ(boost::get<Triangle2D>(area_p.interior_curves.front()).point0().y(), 2);

  ASSERT_DOUBLE_EQ(boost::get<Triangle2D>(area_m.interior_curves.front()).point0().x(), 1);
  ASSERT_DOUBLE_EQ(boost::get<Triangle2D>(area_m.interior_curves.front()).point0().y(), 2);
}

TEST(AREA2D, ROTATE) {
  Area2D area;
  area.exterior_curves.push_back(Circle2D(Point2D(2, 4), 0.5));
  area.interior_curves.push_back(Triangle2D(Point2D(0, 0), Point2D(1, 0), Point2D(2, 4)));

  Area2D area_rotated = rotate(M_PI/2, area);

  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(area_rotated.exterior_curves.front()).center().x(), -4);
  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(area_rotated.exterior_curves.front()).center().y(), 2);
  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(area_rotated.exterior_curves.front()).radius(), 0.5);

  ASSERT_DOUBLE_EQ(boost::get<Triangle2D>(area_rotated.interior_curves.back()).point2().x(), -4);
  ASSERT_DOUBLE_EQ(boost::get<Triangle2D>(area_rotated.interior_curves.back()).point2().y(), 2);
}
