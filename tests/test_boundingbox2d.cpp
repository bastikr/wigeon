#include "wigeon/boundingbox2d.h"
#include "gtest/gtest.h"


using namespace wigeon;

TEST(BOUNDINGBOX2D, OPERATORS) {
  BoundingBox2D boundingbox(1, -2, 3, 7);
  Vector2D vector(2, 3);

  BoundingBox2D r0 = boundingbox + vector;
  BoundingBox2D r1 = vector + boundingbox;
  BoundingBox2D r2 = boundingbox - vector;

  ASSERT_DOUBLE_EQ(r0.xmin(), 3);
  ASSERT_DOUBLE_EQ(r0.ymin(), 1);
  ASSERT_DOUBLE_EQ(r0.xmax(), 5);
  ASSERT_DOUBLE_EQ(r0.ymax(), 10);

  ASSERT_DOUBLE_EQ(r1.xmin(), 3);
  ASSERT_DOUBLE_EQ(r1.ymin(), 1);
  ASSERT_DOUBLE_EQ(r1.xmax(), 5);
  ASSERT_DOUBLE_EQ(r1.ymax(), 10);

  ASSERT_DOUBLE_EQ(r2.xmin(), -1);
  ASSERT_DOUBLE_EQ(r2.ymin(), -5);
  ASSERT_DOUBLE_EQ(r2.xmax(), 1);
  ASSERT_DOUBLE_EQ(r2.ymax(), 4);
}

TEST(BOUNDINGBOX2D, AREA) {
  BoundingBox2D boundingbox(1, -2, 3, 7);
  ASSERT_DOUBLE_EQ(boundingbox.area(), 18);
}

TEST(BOUNDINGBOX2D, OVERLAP) {
  BoundingBox2D box0(1, -2, 3, 7);

  ASSERT_TRUE(overlap(box0, BoundingBox2D(0.5, -3, 1.5, 1)));
  ASSERT_TRUE(overlap(box0, BoundingBox2D(1.5, 6, 1.6, 8)));
  ASSERT_TRUE(overlap(box0, BoundingBox2D(1, 3, 2, 4)));
  ASSERT_TRUE(overlap(box0, BoundingBox2D(2.9, 6.9, 3.1, 7.1)));

  ASSERT_FALSE(overlap(box0, BoundingBox2D(-1, -3, 0.9, -2.9)));
  ASSERT_FALSE(overlap(box0, BoundingBox2D(3.1, 7.1, 3.2, 7.2)));
}

TEST(BOUNDINGBOX2D, COMBINE) {
  BoundingBox2D box0(1, -2, 3, 7);
  BoundingBox2D box1(-3, 1, 2, 8);

  BoundingBox2D result = combine(box0, box1);
  ASSERT_DOUBLE_EQ(result.xmin(), -3);
  ASSERT_DOUBLE_EQ(result.ymin(), -2);
  ASSERT_DOUBLE_EQ(result.xmax(), 3);
  ASSERT_DOUBLE_EQ(result.ymax(), 8);
}
