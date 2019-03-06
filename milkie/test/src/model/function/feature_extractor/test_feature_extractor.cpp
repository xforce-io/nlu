#include <locale>

#include "gtest/gtest.h"

#include "../../../../../src/conf/conf.h"
#include "../../../../../src/core/model/function/feature_extractor/feature_extractor.h"
#include "../../../../../src/core/model/context/context.h"

LOGGER_IMPL(xforce::xforce_logger, L"milkie")

using namespace xforce;
using namespace xforce::nlu::milkie;
using namespace xforce::nlu::basic;

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");
  LOGGER_SYS_INIT(L"../conf/log.conf");

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(testAll, all) {
  std::vector<std::shared_ptr<FeatureExtractor>> featureExtractors;
  ASSERT_TRUE(FeatureExtractor::Build("../../data/global", featureExtractors));

  std::shared_ptr<FeatureExtractor> timeFeatureExtractor;
  for (auto &featureExtractor : featureExtractors) {
    if (featureExtractor->GetName() == L"time") {
      timeFeatureExtractor = featureExtractor;
      break;
    }
  }

  StorageKey storageKey(L"ner.time", L"month");

  auto context = std::make_shared<Context>(L"1992年11月10日");
  auto err = timeFeatureExtractor->MatchPattern(*context);
  ASSERT_TRUE(err == Errno::kOk);

  ASSERT_TRUE(*(context->GetStorageAsStr(storageKey)) == L"11");
  auto storageVal = context->GetStorage(storageKey);
  ASSERT_TRUE(storageVal->Size() == 1);
  ASSERT_TRUE(storageVal->Get()[0].GetOffset() == 5);

  context = std::make_shared<Context>(L"5000年11月10日");
  err = timeFeatureExtractor->MatchPattern(*context);
  ASSERT_TRUE(err == Errno::kNotMatched);

  context = std::make_shared<Context>(L"1932年13月");
  err = timeFeatureExtractor->MatchPattern(*context);
  ASSERT_TRUE(err == Errno::kNotMatched);

  context = std::make_shared<Context>(L"我讲的是1932年11月啊");
  err = timeFeatureExtractor->MatchPattern(*context);
  ASSERT_TRUE(err == Errno::kOk);
  ASSERT_TRUE(*(context->GetStorageAsStr(storageKey)) == L"11");
  storageVal = context->GetStorage(storageKey);
  ASSERT_TRUE(storageVal->Size() == 1);
  ASSERT_TRUE(storageVal->Get()[0].GetOffset() == 9);
}

TEST(testBugfix, test) {
  ASSERT_TRUE(xforce::nlu::milkie::Conf::Get().Init("../conf/milkie.conf"));

  std::vector<std::shared_ptr<FeatureExtractor>> featureExtractors;
  ASSERT_TRUE(FeatureExtractor::Build("../../data/global", featureExtractors));

  std::shared_ptr<FeatureExtractor> testFeatureExtractor;
  for (auto &featureExtractor : featureExtractors) {
    if (featureExtractor->GetName() == L"test") {
      testFeatureExtractor = featureExtractor;
      break;
    }
  }

  StorageKey storageKey(nullptr, L"modifier");

  auto context = std::make_shared<Context>(L"这很奇怪啊");
  Segment::Vector segments;
  segments.push_back(Segment(Pos::kUndef, 0, 1));
  segments.push_back(Segment(Pos::kUndef, 1, 1));
  segments.push_back(Segment(Pos::kUndef, 2, 2));
  segments.push_back(Segment(Pos::kUndef, 4, 1));
  context->GetSentence().GetNluContext()->SetSegments(segments);
 
  auto err = testFeatureExtractor->MatchPattern(*context);
  ASSERT_TRUE(err == Errno::kOk);
  ASSERT_TRUE((*(context->GetStorageAsStr(storageKey)) == L"很"));
}
