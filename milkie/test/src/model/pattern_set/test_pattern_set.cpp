#include <locale>

#include "gtest/gtest.h"

#include "../../../src/core/model/pattern_set/pattern_set.h"

LOGGER_IMPL(xforce::xforce_logger, L"milkie")

using namespace xforce::nlu::milkie;
using namespace xforce::nlu::basic;

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(testAll, build) {
  auto ret = PatternSet::Build(L"global", L"[\"美味的方便面\" && #Pos(aP-uP-nP-), \"就是的\"]");
  std::cout << ret.first->GetPatternExprs().size() << std::endl;
  ASSERT_TRUE(ret.first->GetPatternExprs().size() == 2);

  auto context = std::make_shared<Context>(L"美味的方便面才好吃");
  Segment::Vector segments;
  segments.push_back(Segment(Pos::kA, 0, 2));
  segments.push_back(Segment(Pos::kU, 2, 1));
  segments.push_back(Segment(Pos::kN, 3, 3));
  context->GetSentence().GetNluContext()->SetSegments(segments);
  ASSERT_TRUE(ret.first->MatchPattern(*(context.get())));

  context = std::make_shared<Context>(L"美味的牛肉才好吃");
  ASSERT_TRUE(ret.first->MatchPattern(*(context.get())));

  context = std::make_shared<Context>(L"就是的吗");
  ASSERT_TRUE(ret.first->MatchPattern(*(context.get())));

  context = std::make_shared<Context>(L"就是说吗");
  ASSERT_TRUE(!ret.first->MatchPattern(*(context.get())));

  /*
   * TODO: add global refer
  context = std::make_shared<Context>(L"您好吗");
  ASSERT_TRUE(ret.first->MatchPattern(*(context.get()));
   */
}
