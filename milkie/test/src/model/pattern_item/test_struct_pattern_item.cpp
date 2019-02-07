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

TEST(testAll, testStructPatternItemStr) {
  auto structPatternItemStr = StructPatternItemStr::Build(L"\"123\" balabala");
  ASSERT_TRUE(structPatternItemStr->GetPatternStr() == L"123");
  ASSERT_TRUE(structPatternItemStr->GetArgs().size() == 0);
}

TEST(testAll, testStructPatternItemCommon) {
  auto structPatternItemCommon = StructPatternItemCommon::Build(L"#Pos( (()()) ) abcdefg");
  ASSERT_TRUE(structPatternItemCommon->GetCategory() == CategoryPatternItem::kPos);
  ASSERT_TRUE(structPatternItemCommon->GetArgs().size() == 1);
  ASSERT_TRUE(structPatternItemCommon->GetArgs()[0] == L"(()())");

  structPatternItemCommon = StructPatternItemCommon::Build(L"#Pos()");
  ASSERT_TRUE(structPatternItemCommon == nullptr);
}
