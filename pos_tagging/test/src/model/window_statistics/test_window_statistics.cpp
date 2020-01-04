#include <locale>

#include "gtest/gtest.h"
#include "../../../../src/model/window_statistics/window_statistics.h"
#include "basic/model/fragment/segment.h"
#include "segmentor/segmentor.h"

LOGGER_IMPL(xforce::xforce_logger, L"pos_tagging")

using namespace xforce;
using namespace xforce::nlu::basic;
using namespace xforce::nlu::segmentor;
using namespace xforce::nlu::pos;

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");
  LOGGER_SYS_INIT(L"../../conf/log.conf");

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
/*
TEST(test_case, all) {
  const xforce::JsonType* conf = xforce::JsonType::CreateConf("../conf/pos.conf");
  ASSERT_TRUE(Basic::Init((*conf)["basic"]));
  ASSERT_TRUE(Segmentor::Init((*conf)["segmentor"], (*conf)["ner"]));

  WindowStatistics *windowStatistics = WindowStatistics::Create("../data/labeled_data");
  ASSERT_TRUE(windowStatistics != nullptr);

  auto result = windowStatistics->GetDominator(L"发展", L"的", L"机遇");
  ASSERT_TRUE(result.second != nullptr);

  std::stringstream ss;
  windowStatistics->Dump(ss);

  WindowStatistics *windowStatistics1 = new WindowStatistics();
  int ret = windowStatistics1->Load(ss.str());
  ASSERT_TRUE(0==ret);

  result = windowStatistics1->GetDominator(L"发展", L"的", L"机遇");
  ASSERT_TRUE(result.second != nullptr);

  std::stringstream ss1;
  windowStatistics1->Dump(ss1);

  ASSERT_TRUE(*windowStatistics == *windowStatistics1);
}
*/
TEST(test_case, bugfix) {
  const xforce::JsonType* conf = xforce::JsonType::CreateConf("../conf/pos.conf");
  ASSERT_TRUE(Basic::Init((*conf)["basic"]));
  ASSERT_TRUE(Segmentor::Init((*conf)["segmentor"], (*conf)["ner"]));

  WindowStatistics *windowStatistics = WindowStatistics::Create("../data/labeled_data");
  ASSERT_TRUE(windowStatistics != nullptr);

  auto result = windowStatistics->GetDominator(L"本场", L"比赛");
  ASSERT_TRUE(result.second != nullptr);

  std::stringstream ss;
  windowStatistics->Dump(ss);
  std::cout << ss.str() << std::endl;
}
