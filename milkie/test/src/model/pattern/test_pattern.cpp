#include <locale>

#include "gtest/gtest.h"

#include "../../../src/core/model/pattern/pattern.h"
#include "../../../src/core/model/context/context.h"

LOGGER_IMPL(xforce::xforce_logger, L"milkie")

using namespace xforce::nlu::milkie;
using namespace xforce::nlu::basic;

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(testAll, all) {
  auto ret = Pattern::Build(L"\"美味的方便面\" && #Pos(aP-uP-nP-)");
  ASSERT_TRUE(ret.first->GetPatternItems().size() == 2);

  auto context = std::make_shared<Context>(L"美味的方便面才好吃");
  Segment::Vector segments;
  segments.push_back(Segment(Pos::kA, 0, 2));
  segments.push_back(Segment(Pos::kU, 2, 1));
  segments.push_back(Segment(Pos::kN, 3, 3));
  context->GetSentence().GetNluContext()->SetSegments(segments);
  ASSERT_TRUE(ret.first->MatchPattern(*(context.get())));
  ASSERT_TRUE(context->GetCurPos() == 6);
}

TEST(testAll, badcase) {
  auto ret = Pattern::Build(L"\"美味\"");
  ASSERT_TRUE(ret.first->GetPatternItems().size() == 1);

  auto context = std::make_shared<Context>(L"美味的方便面才好吃");
  ASSERT_TRUE(ret.first->MatchPattern(*(context.get())));
  ASSERT_TRUE(context->GetCurPos() == 2);
}
