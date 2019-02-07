#include <locale>

#include "gtest/gtest.h"

#include "../../../src/core/model/pattern_item/pattern_item.h"
#include "../../../src/core/model/context/context.h"

LOGGER_IMPL(xforce::xforce_logger, L"milkie")

using namespace xforce::nlu::milkie;
using namespace xforce::nlu::basic;

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(testAll, build) {

