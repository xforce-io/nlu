#include "gtest/gtest.h"
#include "../src/data/BigramDict.h"

LOGGER_IMPL(xforce::xforce_logger, "template")

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(test_all, all) {
}
