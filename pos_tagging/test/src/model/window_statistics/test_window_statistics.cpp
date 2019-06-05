#include <locale>

#include "gtest/gtest.h"
#include "../../../../src/model/window_statistics/window_statistics.h"
#include "basic/model/segment.h"
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

TEST(test_case, all) {
  const xforce::JsonType* conf = xforce::JsonType::CreateConf("../conf/pos.conf");
  ASSERT_TRUE(Basic::Init((*conf)["basic"]));
  ASSERT_TRUE(Segmentor::Init((*conf)["segmentor"], (*conf)["ner"]));

  WindowStatistics *windowStatistics = WindowStatistics::Create("../../data/labeled_data.sample");
  ASSERT_TRUE(windowStatistics != nullptr);

  std::stringstream ss;
  windowStatistics->Dump(ss);

  std::cout << ss.str() << std::endl;

  WindowStatistics *windowStatistics1 = new WindowStatistics();
  int ret = windowStatistics1->Load(ss.str());
  ASSERT_TRUE(0==ret);

  std::stringstream ss1;
  windowStatistics1->Dump(ss1);

  std::cout << ss1.str() << std::endl;

  ASSERT_TRUE(ss.str() == ss1.str());
}
