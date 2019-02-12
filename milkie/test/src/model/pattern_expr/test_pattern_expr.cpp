#include <locale>

#include "gtest/gtest.h"

#include "../../../src/milkie.h"
#include "../../../src/core/model/pattern_expr/pattern_expr.h"
#include "../../../src/core/model/refer/refer_manager.h"

LOGGER_IMPL(xforce::xforce_logger, L"milkie")

using namespace xforce::nlu::milkie;
using namespace xforce::nlu::basic;

const static std::wstring kTestBlockKey = L"testBlockKey";

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");
  LOGGER_SYS_INIT(L"../conf/log.conf");

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

void testcase0();
void testcase1();
void testcase2();
void testcaseWildcard();
void testcaseMultimatch();

TEST(testAll, all) {
  ASSERT_TRUE(Milkie::Init("../conf/milkie.conf"));
  ASSERT_TRUE(ReferManager::Get().AddToGlobalDict("../../data/test/dict"));
  testcase0();
  testcase1();
  testcase2();
  testcaseWildcard();
  testcaseMultimatch();
}

void testcase0() {
  auto ret = PatternExpr::Build(kTestBlockKey, L"{$IsAAnchor -> desc }");
  ASSERT_TRUE(ret.second == 21);
}

void testcase1() {
  std::wstring expr = Helper::PreprocessExprLine(L"{#Pos(dP-aP-) | ret = string.len(_pattern_) < 5 | -> target *}");
  auto ret = PatternExpr::Build(kTestBlockKey, expr);
  ASSERT_TRUE(ret.first != nullptr);

  auto context = std::make_shared<Context>(L"不好");
  Segment::Vector segments;
  segments.push_back(Segment(Pos::kD, 0, 1));
  segments.push_back(Segment(Pos::kA, 1, 1));
  context->GetSentence().GetNluContext()->SetSegments(segments);
  ASSERT_TRUE(ret.first->ExactMatch(*(context.get())));
  ASSERT_TRUE(*(context->GetStorageAsStr(L"target")) == L"不好");

  context = std::make_shared<Context>(L"不好不好");
  segments.clear();
  segments.push_back(Segment(Pos::kD, 0, 1));
  segments.push_back(Segment(Pos::kA, 1, 1));
  segments.push_back(Segment(Pos::kD, 2, 1));
  segments.push_back(Segment(Pos::kA, 3, 1));
  context->GetSentence().GetNluContext()->SetSegments(segments);
  ASSERT_TRUE(ret.first->ExactMatch(*(context.get())));

  context = std::make_shared<Context>(L"不好不好机器人");
  segments.clear();
  segments.push_back(Segment(Pos::kD, 0, 1));
  segments.push_back(Segment(Pos::kA, 1, 1));
  segments.push_back(Segment(Pos::kD, 2, 1));
  segments.push_back(Segment(Pos::kA, 3, 1));
  segments.push_back(Segment(Pos::kN, 4, 3));
  context->GetSentence().GetNluContext()->SetSegments(segments);
  ASSERT_TRUE(ret.first->MatchPattern(*(context.get()), false));
}

void testcase2() {
  std::wstring expr = Helper::PreprocessExprLine(L"{ {$ContinousN -> noun} #Pos(dP-aP-) { #Pos(yP-) -> yPhrase *} -> target *}");
  auto ret = PatternExpr::Build(kTestBlockKey, expr);
  ASSERT_TRUE(ret.first != nullptr);

  auto context = std::make_shared<Context>(L"苹果橘子不好吃吧");
  Segment::Vector segments;
  segments.push_back(Segment(Pos::kN, 0, 2));
  segments.push_back(Segment(Pos::kN, 2, 2));
  segments.push_back(Segment(Pos::kD, 4, 1));
  segments.push_back(Segment(Pos::kA, 5, 2));
  segments.push_back(Segment(Pos::kY, 7, 1));
  context->GetSentence().GetNluContext()->SetSegments(segments);
  ASSERT_TRUE(ret.first->ExactMatch(*(context.get())));
  ASSERT_TRUE(*(context->GetStorageAsStr(L"target")) == L"苹果橘子不好吃吧");
  ASSERT_TRUE(*(context->GetStorageAsStr(L"noun")) == L"苹果橘子");
  ASSERT_TRUE(*(context->GetStorageAsStr(L"yPhrase")) == L"吧");

  context = std::make_shared<Context>(L"苹果不好吃");
  segments.clear();
  segments.push_back(Segment(Pos::kN, 0, 2));
  segments.push_back(Segment(Pos::kD, 2, 1));
  segments.push_back(Segment(Pos::kA, 3, 2));
  context->GetSentence().GetNluContext()->SetSegments(segments);
  ASSERT_TRUE(ret.first->ExactMatch(*(context.get())));
  ASSERT_TRUE(*(context->GetStorageAsStr(L"target")) == L"苹果不好吃");
  ASSERT_TRUE(*(context->GetStorageAsStr(L"noun")) == L"苹果");
  ASSERT_TRUE(context->GetStorageAsStr(L"yPhrase") == nullptr);
}

void testcaseWildcard() {
  std::wstring expr = Helper::PreprocessExprLine(L"{ {$ContinousN -> noun} $*Wield #Pos(dP-aP-) { #Pos(yP-) -> yPhrase *} -> target }");
  auto ret = PatternExpr::Build(kTestBlockKey, expr);
  ASSERT_TRUE(ret.first != nullptr);

  std::wstring pattern = L"苹果橘子真的真的不好吃吧";
  auto context = std::make_shared<Context>(pattern);
  Segment::Vector segments;
  segments.push_back(Segment(Pos::kN, 0, 2));
  segments.push_back(Segment(Pos::kN, 2, 2));
  segments.push_back(Segment(Pos::kD, 4, 2));
  segments.push_back(Segment(Pos::kD, 6, 2));
  segments.push_back(Segment(Pos::kD, 8, 1));
  segments.push_back(Segment(Pos::kA, 9, 2));
  segments.push_back(Segment(Pos::kY,11, 1));
  context->GetSentence().GetNluContext()->SetSegments(segments);
  ASSERT_TRUE(ret.first->ExactMatch(*(context.get())));
  ASSERT_TRUE(*(context->GetStorageAsStr(L"Wield")) == L"真的真的");
  ASSERT_TRUE(*(context->GetStorageAsStr(L"target")) == pattern);
  ASSERT_TRUE(*(context->GetStorageAsStr(L"noun")) == L"苹果橘子");
  ASSERT_TRUE(*(context->GetStorageAsStr(L"yPhrase")) == L"吧");

  expr = Helper::PreprocessExprLine(L"{ {$ContinousN -> noun} $*Wield #Pos(v) #Pos(yP-) }");
  ret = PatternExpr::Build(kTestBlockKey, expr);
  ASSERT_TRUE(ret.first != nullptr);

  pattern = L"苹果橘子真的真的不好吃是吧";
  context = std::make_shared<Context>(pattern);
  segments.clear();
  segments.push_back(Segment(Pos::kN, 0, 2));
  segments.push_back(Segment(Pos::kN, 2, 2));
  segments.push_back(Segment(Pos::kD, 4, 2));
  segments.push_back(Segment(Pos::kD, 6, 2));
  segments.push_back(Segment(Pos::kD, 8, 1));
  segments.push_back(Segment(Pos::kA, 9, 2));
  segments.push_back(Segment(Pos::kV,11, 1));
  segments.push_back(Segment(Pos::kY,12, 1));
  context->GetSentence().GetNluContext()->SetSegments(segments);
  ASSERT_TRUE(ret.first->ExactMatch(*(context.get())));
  ASSERT_TRUE(*(context->GetStorageAsStr(L"Wield")) == L"真的真的不好吃");

  expr = Helper::PreprocessExprLine(L"{ {$ContinousN -> noun} $*Wield }");
  ret = PatternExpr::Build(kTestBlockKey, expr);
  ASSERT_TRUE(ret.first != nullptr);

  pattern = L"苹果橘子真的真的不好吃";
  context = std::make_shared<Context>(pattern);
  segments.clear();
  segments.push_back(Segment(Pos::kN, 0, 2));
  segments.push_back(Segment(Pos::kN, 2, 2));
  segments.push_back(Segment(Pos::kD, 4, 2));
  segments.push_back(Segment(Pos::kD, 6, 2));
  segments.push_back(Segment(Pos::kD, 8, 1));
  segments.push_back(Segment(Pos::kA, 9, 2));
  context->GetSentence().GetNluContext()->SetSegments(segments);
  ASSERT_TRUE(ret.first->ExactMatch(*(context.get())));
  ASSERT_TRUE(*(context->GetStorageAsStr(L"Wield")) == L"真的真的不好吃");
}

void testcaseMultimatch() {
  std::wstring expr = Helper::PreprocessExprLine(L"{ {$ContinousN -> noun} #Pos(dP-aP-) { #Pos(yP-) -> yPhrase *} -> target }");
  auto ret = PatternExpr::Build(kTestBlockKey, expr);
  ASSERT_TRUE(ret.first != nullptr);

  std::wstring pattern = L"苹果橘子不好吃吧吧";
  auto context = std::make_shared<Context>(pattern);
  Segment::Vector segments;
  segments.push_back(Segment(Pos::kN, 0, 2));
  segments.push_back(Segment(Pos::kN, 2, 2));
  segments.push_back(Segment(Pos::kD, 4, 1));
  segments.push_back(Segment(Pos::kA, 5, 2));
  segments.push_back(Segment(Pos::kY, 7, 1));
  segments.push_back(Segment(Pos::kY, 8, 1));
  context->GetSentence().GetNluContext()->SetSegments(segments);
  ASSERT_TRUE(ret.first->ExactMatch(*(context.get())));
  ASSERT_TRUE(context->GetStorage(L"yPhrase")->Size() == 2);

  pattern = L"苹果橘子不好吃";
  context = std::make_shared<Context>(pattern);
  segments.clear();
  segments.push_back(Segment(Pos::kN, 0, 2));
  segments.push_back(Segment(Pos::kN, 2, 2));
  segments.push_back(Segment(Pos::kD, 4, 1));
  segments.push_back(Segment(Pos::kA, 5, 2));
  context->GetSentence().GetNluContext()->SetSegments(segments);
  ASSERT_TRUE(ret.first->ExactMatch(*(context.get())));
  ASSERT_TRUE(context->GetStorage(L"yPhrase") == nullptr);

  expr = Helper::PreprocessExprLine(L"{ {$ContinousN -> noun} #Pos(dP-aP-) { #Pos(yP-) -> yPhrase +} -> target }");
  ret = PatternExpr::Build(kTestBlockKey, expr);
  ASSERT_TRUE(ret.first != nullptr);

  pattern = L"苹果橘子不好吃吧吧";
  context = std::make_shared<Context>(pattern);
  segments.clear();
  segments.push_back(Segment(Pos::kN, 0, 2));
  segments.push_back(Segment(Pos::kN, 2, 2));
  segments.push_back(Segment(Pos::kD, 4, 1));
  segments.push_back(Segment(Pos::kA, 5, 2));
  segments.push_back(Segment(Pos::kY, 7, 1));
  segments.push_back(Segment(Pos::kY, 8, 1));
  context->GetSentence().GetNluContext()->SetSegments(segments);
  ASSERT_TRUE(ret.first->ExactMatch(*(context.get())));
  ASSERT_TRUE(context->GetStorage(L"yPhrase")->Size() == 2);

  pattern = L"苹果橘子不好吃";
  context = std::make_shared<Context>(pattern);
  segments.clear();
  segments.push_back(Segment(Pos::kN, 0, 2));
  segments.push_back(Segment(Pos::kN, 2, 2));
  segments.push_back(Segment(Pos::kD, 4, 1));
  segments.push_back(Segment(Pos::kA, 5, 2));
  context->GetSentence().GetNluContext()->SetSegments(segments);
  ASSERT_TRUE(!ret.first->ExactMatch(*(context.get())));
}
