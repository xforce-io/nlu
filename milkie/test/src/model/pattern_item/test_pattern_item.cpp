#include <locale>

#include "gtest/gtest.h"

#include "../../../src/core/model/pattern_item/pattern_item.h"
#include "../../../src/core/model/pattern_item/pattern_item_str.h"
#include "../../../src/core/model/pattern_item/pattern_item_wordpos.h"
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
  auto ret = PatternItem::Build(L"\"123\" 12");
  ASSERT_TRUE(typeid(*(ret.first)) == typeid(PatternItemStr));

  PatternItemStr *patternItemStr = SCAST<PatternItemStr*>(ret.first.get()); 
  ASSERT_TRUE(patternItemStr->GetPatternStr() == L"123");
  ASSERT_TRUE(ret.second == 5);

  ret = PatternItem::Build(L"#Pos(  abcd  )  321 ");
  ASSERT_TRUE(typeid(*(ret.first)) == typeid(PatternItemWordpos));
}

TEST(testAll, match) {
  auto ret = PatternItem::Build(L"\"123\" 12");
  std::shared_ptr<Context> context = std::make_shared<Context>(L"123");
  ASSERT_TRUE(ret.first->MatchPattern(*context));

  context = std::make_shared<Context>(L"12");
  ASSERT_TRUE(!ret.first->MatchPattern(*(context.get())));

  ret = PatternItem::Build(L"#Pos((n|a)P-uP-nP-)");

  auto query = L"美味的方便面才好吃";
  context = std::make_shared<Context>(query);

  FragmentSet<Segment> segments(query);
  segments.Add(Segment(PosTag::Type::kA, 0, 2));
  segments.Add(Segment(PosTag::Type::kU, 2, 1));
  segments.Add(Segment(PosTag::Type::kN, 3, 3));
  context->GetSentence().GetNluContext()->SetSegments(segments);
  ASSERT_TRUE(ret.first->MatchPattern(*(context.get())));

  ret = PatternItem::Build(L"#Reg(\\d{4}年\\d{2}月)");

  context = std::make_shared<Context>(L"2012年12月11号");
  ASSERT_TRUE(ret.first->MatchPattern(*(context.get())));
  ASSERT_TRUE(ret.first->GetContentMatched() == L"2012年12月");
}

TEST(testAll, multiSegMatch) {
  auto query = L"美味的方便面才好吃";
  std::shared_ptr<Context> context = std::make_shared<Context>(query);

  FragmentSet<Segment> segments(query);
  segments.Add(Segment(PosTag::Type::kA, 0, 2));
  (*segments.Begin())->AddPosTag(PosTag::Type::kN);

  segments.Add(Segment(PosTag::Type::kU, 2, 1));
  segments.Add(Segment(PosTag::Type::kN, 3, 3));
  context->GetSentence().GetNluContext()->SetSegments(segments);

  auto ret = PatternItem::Build(L"#Pos((n|a)P-uP-nP-)");
  ASSERT_TRUE(ret.first->MatchPattern(*(context.get())));
}
