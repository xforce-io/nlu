#include <locale>

#include "gtest/gtest.h"

#include "../../../src/core/model/pattern_item/parser/struct_pattern_item_common.h"
#include "../../../src/core/model/pattern_item/parser/struct_pattern_item_str.h"

LOGGER_IMPL(xforce::xforce_logger, L"milkie")

using namespace xforce::nlu::milkie;

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(testAll, testPatternItemReprStr) {
  auto structPatternItemStr = StructPatternItemStr::Build("\"123\" balabala");
  ASSERT_TRUE(structPatternItemStr.GetStatement() == "\"123\"");
}

TEST(testAll, testPatternItemReprCommon) {

}