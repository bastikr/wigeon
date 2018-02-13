#include "wigeon/binarytree2d.h"
#include "gtest/gtest.h"

#include <cmath>


using namespace wigeon;


TEST(BINARYTREE, INSERTION) {
  wigeon::BinaryTree node(BoundingBox2D(0, 0, 10, 10), 1);
  node.insert(4, BoundingBox2D(1, 1, 3, 3));

  std::vector<int> results = node.find(BoundingBox2D(2, 2, 2.1, 2.1));
  ASSERT_EQ(results.size(), 1);
  ASSERT_EQ(results.front(), 4);
}
