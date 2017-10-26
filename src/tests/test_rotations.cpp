#include "geometry/rotations.h"
#include "gtest/gtest.h"

using namespace geometry::rotations;

TEST(Rotations, EulerAngles) {
  auto R = RotationMatrix::rotate_x(0.5);
  EXPECT_EQ(RotationMatrix::rotate_x(0.1).data, RotationMatrix::rotate_x(0.1).data);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}