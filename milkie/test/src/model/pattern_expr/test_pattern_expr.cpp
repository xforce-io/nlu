#include <locale>

#include "gtest/gtest.h"

#include "../../../src/milkie.h"
#include "../../../src/core/model/pattern_expr/pattern_expr.h"
#include "../../../src/core/model/refer/refer_manager.h"

LOGGER_IMPL(xforce::xforce_logger, L"milkie")

using namespace xforce::nlu::milkie;
using namespace xforce::nlu::basic;

const static std::wstring kTestBlockKey = L"testBlockKey";

Milkie *milkie;

void initMilkie() {
  milkie = new Milkie();
  assert(milkie->Init("../conf/milkie.conf"));
}

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");
  LOGGER_SYS_INIT(L"../conf/log.conf");

  initMilkie();

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

void testcase0();
void testcase1();
void testcase2();
void testcaseWildcard();
void testcaseMultimatch();

TEST(testAll, all) {
  ASSERT_TRUE(milkie->GetReferManager().AddToGlobalDict("../../data/test/dict"));
  testcase0();
  testcase1();
  testcase2();
  testcaseWildcard();
  testcaseMultimatch();
}

void testcase0() {
  auto ret = PatternExpr::Build(milkie->GetReferManager(), kTestBlockKey, L"{$IsAAnchor -> desc }");
  ASSERT_TRUE(ret.second == 21);
}

void testcase1() {
  std::wstring expr = Helper::PreprocessExprLine(L"{#Pos(dP-aP-) | ret = _pl_ < 5 | -> target *}");
  auto ret = PatternExpr::Build(milkie->GetReferManager(), kTestBlockKey, expr);
  ASSERT_TRUE(ret.first != nullptr);

  auto query = L"不好";
  FragmentSet<Segment> segments(query);
  auto context = std::make_shared<Context>(query);
  segments.Add(Segment(PosTag::Type::kD, 0, 1));
  segments.Add(Segment(PosTag::Type::kA, 1, 1));
  context->GetSentence().GetNluContext()->SetSegments(segments);
  ASSERT_TRUE(ret.first->ExactMatch(*(context.get())));
  ASSERT_TRUE(*(context->GetCurStorageAsStr(L"target")) == L"不好");

  query = L"不好不好";
  context = std::make_shared<Context>(query);
  segments.Reset(query);
  segments.Add(Segment(PosTag::Type::kD, 0, 1));
  segments.Add(Segment(PosTag::Type::kA, 1, 1));
  segments.Add(Segment(PosTag::Type::kD, 2, 1));
  segments.Add(Segment(PosTag::Type::kA, 3, 1));
  context->GetSentence().GetNluContext()->SetSegments(segments);
  ASSERT_TRUE(ret.first->ExactMatch(*(context.get())));

  query = L"不好不好机器人";
  context = std::make_shared<Context>(query);
  segments.Reset(query);
  segments.Add(Segment(PosTag::Type::kD, 0, 1));
  segments.Add(Segment(PosTag::Type::kA, 1, 1));
  segments.Add(Segment(PosTag::Type::kD, 2, 1));
  segments.Add(Segment(PosTag::Type::kA, 3, 1));
  segments.Add(Segment(PosTag::Type::kN, 4, 3));
  context->GetSentence().GetNluContext()->SetSegments(segments);
  ASSERT_TRUE(ret.first->PrefixMatch(*(context.get()), false));
}

void testcase2() {
  std::wstring expr = Helper::PreprocessExprLine(L"{ {$ContinousN -> noun} #Pos(dP-aP-) { #Pos(yP-) -> yPhrase *} => target *}");
  auto ret = PatternExpr::Build(milkie->GetReferManager(), kTestBlockKey, expr);
  ASSERT_TRUE(ret.first != nullptr);

  auto query = L"苹果橘子不好吃吧";
  auto context = std::make_shared<Context>(query);
  FragmentSet<Segment> segments(query);
  segments.Add(Segment(PosTag::Type::kN, 0, 2));
  segments.Add(Segment(PosTag::Type::kN, 2, 2));
  segments.Add(Segment(PosTag::Type::kD, 4, 1));
  segments.Add(Segment(PosTag::Type::kA, 5, 2));
  segments.Add(Segment(PosTag::Type::kY, 7, 1));
  context->GetSentence().GetNluContext()->SetSegments(segments);
  ASSERT_TRUE(ret.first->ExactMatch(*(context.get())));
  ASSERT_TRUE(*(context->GetCurStorageAsStr(*new StorageKey(L"target", nullptr))) == L"苹果橘子不好吃吧");
  ASSERT_TRUE(*(context->GetCurStorageAsStr(*new StorageKey(L"target", L"noun"))) == L"苹果橘子");
  ASSERT_TRUE(*(context->GetCurStorageAsStr(*new StorageKey(L"target", L"yPhrase"))) == L"吧");

  query = L"苹果不好吃";
  context = std::make_shared<Context>(query);
  segments.Reset(query);
  segments.Add(Segment(PosTag::Type::kN, 0, 2));
  segments.Add(Segment(PosTag::Type::kD, 2, 1));
  segments.Add(Segment(PosTag::Type::kA, 3, 2));
  context->GetSentence().GetNluContext()->SetSegments(segments);
  ASSERT_TRUE(ret.first->ExactMatch(*(context.get())));
  ASSERT_TRUE(*(context->GetCurStorageAsStr(*new StorageKey(L"target", nullptr))) == L"苹果不好吃");
  ASSERT_TRUE(*(context->GetCurStorageAsStr(*new StorageKey(L"target", L"noun"))) == L"苹果");
  ASSERT_TRUE(context->GetCurStorageAsStr(*new StorageKey(L"target", L"yPhrase")) == nullptr);
}

void testcaseWildcard() {
  std::cout << "A" << std::endl;

  std::wstring expr = Helper::PreprocessExprLine(L"{ {$ContinousN -> noun} $*Wield #Pos(dP-aP-) { #Pos(yP-) -> yPhrase *} -> target }");
  auto ret = PatternExpr::Build(milkie->GetReferManager(), kTestBlockKey, expr);
  ASSERT_TRUE(ret.first != nullptr);

  std::cout << "A.1" << std::endl;

  std::wstring query = L"苹果橘子真的真的不好吃吧";
  auto context = std::make_shared<Context>(query);
  FragmentSet<Segment> segments(query);
  segments.Add(Segment(PosTag::Type::kN, 0, 2));
  segments.Add(Segment(PosTag::Type::kN, 2, 2));
  segments.Add(Segment(PosTag::Type::kD, 4, 2));
  segments.Add(Segment(PosTag::Type::kD, 6, 2));
  segments.Add(Segment(PosTag::Type::kD, 8, 1));
  segments.Add(Segment(PosTag::Type::kA, 9, 2));
  segments.Add(Segment(PosTag::Type::kY,11, 1));
  context->GetSentence().GetNluContext()->SetSegments(segments);
  std::cout << "A.2" << std::endl;
  ASSERT_TRUE(ret.first->ExactMatch(*(context.get())));
  std::cout << "A.3" << std::endl;
  ASSERT_TRUE(*(context->GetCurStorageAsStr(L"Wield")) == L"真的真的");
  ASSERT_TRUE(*(context->GetCurStorageAsStr(L"target")) == query);
  ASSERT_TRUE(*(context->GetCurStorageAsStr(L"noun")) == L"苹果橘子");
  ASSERT_TRUE(*(context->GetCurStorageAsStr(L"yPhrase")) == L"吧");

  std::cout << "B" << std::endl;

  expr = Helper::PreprocessExprLine(L"{ {$ContinousN -> noun} $*Wield #Pos(v) #Pos(yP-) }");
  ret = PatternExpr::Build(milkie->GetReferManager(), kTestBlockKey, expr);
  ASSERT_TRUE(ret.first != nullptr);

  query = L"苹果橘子真的真的不好吃是吧";
  context = std::make_shared<Context>(query);
  segments.Reset(query);
  segments.Add(Segment(PosTag::Type::kN, 0, 2));
  segments.Add(Segment(PosTag::Type::kN, 2, 2));
  segments.Add(Segment(PosTag::Type::kD, 4, 2));
  segments.Add(Segment(PosTag::Type::kD, 6, 2));
  segments.Add(Segment(PosTag::Type::kD, 8, 1));
  segments.Add(Segment(PosTag::Type::kA, 9, 2));
  segments.Add(Segment(PosTag::Type::kV,11, 1));
  segments.Add(Segment(PosTag::Type::kY,12, 1));
  context->GetSentence().GetNluContext()->SetSegments(segments);
  ASSERT_TRUE(ret.first->ExactMatch(*(context.get())));
  ASSERT_TRUE(*(context->GetCurStorageAsStr(L"Wield")) == L"真的真的不好吃");

  std::cout << "C" << std::endl;

  expr = Helper::PreprocessExprLine(L"{ {$ContinousN -> noun} $*Wield }");
  ret = PatternExpr::Build(milkie->GetReferManager(), kTestBlockKey, expr);
  ASSERT_TRUE(ret.first != nullptr);

  query = L"苹果橘子真的真的不好吃";
  context = std::make_shared<Context>(query);
  segments.Reset(query);
  segments.Add(Segment(PosTag::Type::kN, 0, 2));
  segments.Add(Segment(PosTag::Type::kN, 2, 2));
  segments.Add(Segment(PosTag::Type::kD, 4, 2));
  segments.Add(Segment(PosTag::Type::kD, 6, 2));
  segments.Add(Segment(PosTag::Type::kD, 8, 1));
  segments.Add(Segment(PosTag::Type::kA, 9, 2));
  context->GetSentence().GetNluContext()->SetSegments(segments);
  ASSERT_TRUE(ret.first->ExactMatch(*(context.get())));
  ASSERT_TRUE(*(context->GetCurStorageAsStr(L"Wield")) == L"真的真的不好吃");

  std::cout << "D" << std::endl;
}

void testcaseMultimatch() {
  std::wstring expr = Helper::PreprocessExprLine(L"{ {$ContinousN -> noun} #Pos(dP-aP-) { #Pos(yP-) -> yPhrase *} -> target }");
  auto ret = PatternExpr::Build(milkie->GetReferManager(), kTestBlockKey, expr);
  ASSERT_TRUE(ret.first != nullptr);

  std::wstring query = L"苹果橘子不好吃吧吧";
  auto context = std::make_shared<Context>(query);
  FragmentSet<Segment> segments(query);
  segments.Add(Segment(PosTag::Type::kN, 0, 2));
  segments.Add(Segment(PosTag::Type::kN, 2, 2));
  segments.Add(Segment(PosTag::Type::kD, 4, 1));
  segments.Add(Segment(PosTag::Type::kA, 5, 2));
  segments.Add(Segment(PosTag::Type::kY, 7, 1));
  segments.Add(Segment(PosTag::Type::kY, 8, 1));
  context->GetSentence().GetNluContext()->SetSegments(segments);
  ASSERT_TRUE(ret.first->ExactMatch(*(context.get())));
  ASSERT_TRUE(context->GetCurStorage(L"yPhrase")->Size() == 2);

  query = L"苹果橘子不好吃";
  context = std::make_shared<Context>(query);
  segments.Reset(query);
  segments.Add(Segment(PosTag::Type::kN, 0, 2));
  segments.Add(Segment(PosTag::Type::kN, 2, 2));
  segments.Add(Segment(PosTag::Type::kD, 4, 1));
  segments.Add(Segment(PosTag::Type::kA, 5, 2));
  context->GetSentence().GetNluContext()->SetSegments(segments);
  ASSERT_TRUE(ret.first->ExactMatch(*(context.get())));
  ASSERT_TRUE(context->GetCurStorage(L"yPhrase") == nullptr);

  expr = Helper::PreprocessExprLine(L"{ {$ContinousN -> noun} #Pos(dP-aP-) { #Pos(yP-) -> yPhrase +} -> target }");
  ret = PatternExpr::Build(milkie->GetReferManager(), kTestBlockKey, expr);
  ASSERT_TRUE(ret.first != nullptr);

  query = L"苹果橘子不好吃吧吧";
  context = std::make_shared<Context>(query);
  segments.Reset(query);
  segments.Add(Segment(PosTag::Type::kN, 0, 2));
  segments.Add(Segment(PosTag::Type::kN, 2, 2));
  segments.Add(Segment(PosTag::Type::kD, 4, 1));
  segments.Add(Segment(PosTag::Type::kA, 5, 2));
  segments.Add(Segment(PosTag::Type::kY, 7, 1));
  segments.Add(Segment(PosTag::Type::kY, 8, 1));
  context->GetSentence().GetNluContext()->SetSegments(segments);
  ASSERT_TRUE(ret.first->ExactMatch(*(context.get())));
  ASSERT_TRUE(context->GetCurStorage(L"yPhrase")->Size() == 2);

  query = L"苹果橘子不好吃";
  context = std::make_shared<Context>(query);
  segments.Reset(query);
  segments.Add(Segment(PosTag::Type::kN, 0, 2));
  segments.Add(Segment(PosTag::Type::kN, 2, 2));
  segments.Add(Segment(PosTag::Type::kD, 4, 1));
  segments.Add(Segment(PosTag::Type::kA, 5, 2));
  context->GetSentence().GetNluContext()->SetSegments(segments);
  ASSERT_TRUE(!ret.first->ExactMatch(*(context.get())));
}
