#include "geometry/rotations.h"
#include "gtest/gtest.h"

using namespace geometry::rotations;

TEST(Rotations, EulerAngles) {
    EXPECT_EQ(eulerangles::x(0.1), eulerangles::x(0.1));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}