#include <locale>

#include "gtest/gtest.h"

#include "../../../src/core/model/pattern_expr/pattern_expr.h"
#include "../../../src/milkie.h"

LOGGER_IMPL(xforce::xforce_logger, L"milkie")

using namespace xforce::nlu::milkie;
using namespace xforce::nlu::basic;

const static std::wstring kTestBlockKey = L"testBlockKey";

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

void testcase0();

TEST(testAll, all) {
  ASSERT_TRUE(Milkie::Init("conf/milkie.conf"));
  testcase0();
}

void testcase0() {
  auto ret = PatternExpr::Build(kTestBlockKey, L"{$IsAAnchor -> desc}");
  ASSERT_TRUE(ret.second == 21);
}
