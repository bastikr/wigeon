#include "wigeon/polygon2d_simplification.h"
#include "gtest/gtest.h"

using namespace wigeon;


TEST(POLYGONSIMPLIFICATION, DOUGLAS_PEUCKER0) {
  Polygon2D polygon;
  ASSERT_EQ(douglas_peucker(polygon, 100).size(), 0);

  polygon.append(0, 0);
  ASSERT_EQ(douglas_peucker(polygon, 100).size(), 1);
}

TEST(POLYGONSIMPLIFICATION, DOUGLAS_PEUCKER1) {
  Polygon2D polygon;
  polygon.append(0, 0);
  polygon.append(1, 0.1);
  polygon.append(2, 0);
  polygon.append(1, 1);
  polygon.append(0.5, 1);

  ASSERT_EQ(douglas_peucker(polygon, 0.09).size(), 5);
  ASSERT_EQ(douglas_peucker(polygon, 0.11).size(), 4);
  ASSERT_EQ(douglas_peucker(polygon, 0.36).size(), 3);
  ASSERT_EQ(douglas_peucker(polygon, 1.5).size(), 2);
  ASSERT_EQ(douglas_peucker(polygon, 2.1).size(), 1);
  ASSERT_EQ(douglas_peucker(polygon, 100).size(), 1);
}
