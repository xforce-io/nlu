#include <locale>

#include "gtest/gtest.h"
#include "../../src/pos_tagging.h"
#include "../../src/conf/conf.h"

LOGGER_IMPL(xforce::xforce_logger, L"pos_tagging")

using namespace xforce;
using namespace xforce::nlu::basic;
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
  ASSERT_TRUE(PosTagging::Init((*conf)["pos"]));

  std::wstring query = L"第一局比赛失利原因主要在我们自己";
  NluContext nluContext(query);
  nluContext.GetSegments().Add(Segment(PosTag::kUndef, 0, 2));
  nluContext.GetSegments().Add(Segment(PosTag::kUndef, 2, 1));
  nluContext.GetSegments().Add(Segment(PosTag::kUndef, 3, 2));
  nluContext.GetSegments().Add(Segment(PosTag::kUndef, 5, 2));
  nluContext.GetSegments().Add(Segment(PosTag::kUndef, 7, 2));
  nluContext.GetSegments().Add(Segment(PosTag::kUndef, 9, 2));
  nluContext.GetSegments().Add(Segment(PosTag::kUndef,11, 1));
  nluContext.GetSegments().Add(Segment(PosTag::kUndef,12, 2));
  nluContext.GetSegments().Add(Segment(PosTag::kUndef,14, 2));

  PosTagging::Tagging(nluContext);

  xforce::JsonType jsonToDump;
  nluContext.GetSegments().Dump(jsonToDump);

  std::stringstream ss;
  jsonToDump.DumpJson(ss);
  std::cout << ss.str() << std::endl;
}
