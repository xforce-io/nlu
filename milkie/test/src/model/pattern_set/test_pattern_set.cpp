#include <locale>

#include "gtest/gtest.h"

#include "../../../src/milkie.h"
#include "../../../src/core/model/pattern_set/pattern_set.h"

LOGGER_IMPL(xforce::xforce_logger, L"milkie")

using namespace xforce::nlu::milkie;
using namespace xforce::nlu::basic;

Milkie *milkie;

void initMilkie() {
  milkie = new Milkie();
  assert(milkie->Init("../conf/milkie.conf"));
}

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");

  initMilkie();

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(testAll, build) {
  auto ret = PatternSet::Build(milkie->GetReferManager(), L"global", L"[\"美味的方便面\" && #Pos(aP-uP-nP-), \"就是的\"]");
  ASSERT_TRUE(ret.first->GetPatternExprs()->size() == 2);

  auto query = L"美味的方便面才好吃";
  auto context = std::make_shared<Context>(query);
  FragmentSet<Segment> segments(query);
  segments.Add(Segment(PosTag::Type::kA, 0, 2));
  segments.Add(Segment(PosTag::Type::kU, 2, 1));
  segments.Add(Segment(PosTag::Type::kN, 3, 3));
  context->GetSentence().GetNluContext()->SetSegments(segments);
  ASSERT_TRUE(ret.first->MatchPattern(*(context.get())));

  context = std::make_shared<Context>(L"美味的牛肉才好吃");
  ASSERT_TRUE(!ret.first->MatchPattern(*(context.get())));

  context = std::make_shared<Context>(L"就是的吗");
  ASSERT_TRUE(ret.first->MatchPattern(*(context.get())));

  context = std::make_shared<Context>(L"就是说吗");
  ASSERT_TRUE(!ret.first->MatchPattern(*(context.get())));
}

TEST(testAll, build1) {
  auto ret = PatternSet::Build(milkie->GetReferManager(), L"global", L"[$a, $b]");
  ASSERT_TRUE(ret.first->GetPatternExprs()->size() == 2);

  auto context = std::make_shared<Context>(L"0");
  ASSERT_TRUE(ret.first->MatchPattern(*(context.get())));

  context = std::make_shared<Context>(L"2");
  ASSERT_TRUE(!ret.first->MatchPattern(*(context.get())));
}
