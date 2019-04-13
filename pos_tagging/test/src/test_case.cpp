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

  std::wstring query = L"但却在本场比赛给了中国队强有力的冲击";
  NluContext nluContext(query);
  nluContext.GetSegments().Add(Segment(PosTag::kUndef, 0, 1));
  nluContext.GetSegments().Add(Segment(PosTag::kUndef, 1, 1));
  nluContext.GetSegments().Add(Segment(PosTag::kUndef, 2, 1));
  nluContext.GetSegments().Add(Segment(PosTag::kUndef, 3, 1));
  nluContext.GetSegments().Add(Segment(PosTag::kUndef, 4, 1));
  nluContext.GetSegments().Add(Segment(PosTag::kUndef, 5, 2));
  nluContext.GetSegments().Add(Segment(PosTag::kUndef, 7, 1));
  nluContext.GetSegments().Add(Segment(PosTag::kUndef, 8, 1));
  nluContext.GetSegments().Add(Segment(PosTag::kUndef, 9, 2));
  nluContext.GetSegments().Add(Segment(PosTag::kUndef,11, 1));
  nluContext.GetSegments().Add(Segment(PosTag::kUndef,12, 3));
  nluContext.GetSegments().Add(Segment(PosTag::kUndef,15, 1));
  nluContext.GetSegments().Add(Segment(PosTag::kUndef,16, 2));

  PosTagging::Tagging(nluContext);

  xforce::JsonType jsonToDump;
  nluContext.GetSegments().Dump(jsonToDump);

  std::stringstream ss;
  jsonToDump.DumpJson(ss);
  std::cout << ss.str() << std::endl;
}
