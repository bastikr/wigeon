#include "wigeon/polygon2d_simplification.h"
#include "gtest/gtest.h"

using namespace wigeon;


TEST(POLYGONSIMPLIFICATION, DOUGLAS_PEUCKER0) {
  Polygon2D polygon;
  ASSERT_EQ(douglas_peucker(polygon, 100).size(), 0);

  polygon.push_back(0, 0);
  ASSERT_EQ(douglas_peucker(polygon, 100).size(), 1);
}

TEST(POLYGONSIMPLIFICATION, DOUGLAS_PEUCKER1) {
  Polygon2D polygon;
  polygon.push_back(0, 0);
  polygon.push_back(1, 0.1);
  polygon.push_back(2, 0);
  polygon.push_back(1, 1);
  polygon.push_back(0.5, 1);

  ASSERT_EQ(douglas_peucker(polygon, 0.09).size(), 5);
  ASSERT_EQ(douglas_peucker(polygon, 0.11).size(), 4);
  ASSERT_EQ(douglas_peucker(polygon, 0.36).size(), 3);
  ASSERT_EQ(douglas_peucker(polygon, 1.5).size(), 2);
  ASSERT_EQ(douglas_peucker(polygon, 2.1).size(), 1);
  ASSERT_EQ(douglas_peucker(polygon, 100).size(), 1);
}

TEST(POLYLINESIMPLIFICATION, DOUGLAS_PEUCKER1) {
  PolyLine2D polyline;
  polyline.push_back(0, 0);
  polyline.push_back(1, 0.1);
  polyline.push_back(2, 0);
  polyline.push_back(1, 1);
  polyline.push_back(0, 1);

  ASSERT_EQ(douglas_peucker(polyline, 0.09).size(), 5);
  ASSERT_EQ(douglas_peucker(polyline, 0.11).size(), 4);
  ASSERT_EQ(douglas_peucker(polyline, 0.3).size(), 4);
  ASSERT_EQ(douglas_peucker(polyline, 1.1).size(), 3);
  ASSERT_EQ(douglas_peucker(polyline, 2.1).size(), 2);
  ASSERT_EQ(douglas_peucker(polyline, 100).size(), 2);
}
