#include <locale>

#include "gtest/gtest.h"

#include "../../../../../src/core/model/function/feature_extractor/feature_extractor.h"
#include "../../../../../src/core/model/context/context.h"

LOGGER_IMPL(xforce::xforce_logger, L"milkie")

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

  auto context = std::make_shared<Context>(L"1992年11月10日");
  auto err = timeFeatureExtractor->MatchPattern(*context);
  ASSERT_TRUE(err == Errno::kOk);
  ASSERT_TRUE(*(context->GetStorageAsStr(StorageKey(L"ner.time", L"month"))) == L"11");

  context = std::make_shared<Context>(L"5000年11月10日");
  err = timeFeatureExtractor->MatchPattern(*context);
  ASSERT_TRUE(err == Errno::kNotMatched);

  context = std::make_shared<Context>(L"1932年13月");
  err = timeFeatureExtractor->MatchPattern(*context);
  ASSERT_TRUE(err == Errno::kNotMatched);
}
