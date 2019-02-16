#include <locale>

#include "gtest/gtest.h"

#include "../../../../../src/core/model/function/feature_extractor/feature_extractor.h"

LOGGER_IMPL(xforce::xforce_logger, L"milkie")

using namespace xforce::nlu::milkie;
using namespace xforce::nlu::basic;

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(testAll, all) {
  std::vector<std::shared_ptr<FeatureExtractor>> featureExtractors;
  ASSERT_TRUE(FeatureExtractor::Build("../../data/global", featureExtractors));
}
