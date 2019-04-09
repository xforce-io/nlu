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

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(test_case, all) {
  const xforce::JsonType* conf = xforce::JsonType::CreateConf("conf/pos.conf");
  ASSERT_TRUE(PosTagging::Init((*conf)["pos"]));

  std::wstring query = L"这真的不是太好吧";
  basic::NluContext nluContext(query);
  nluContext.GetSegments().Add(Segment(PosTag::kUndef, 0, 1));
  nluContext.GetSegments().Add(Segment(PosTag::kUndef, 1, 2));
  nluContext.GetSegments().Add(Segment(PosTag::kUndef, 3, 1));
  nluContext.GetSegments().Add(Segment(PosTag::kUndef, 4, 1));
  nluContext.GetSegments().Add(Segment(PosTag::kUndef, 5, 2));
  nluContext.GetSegments().Add(Segment(PosTag::kUndef, 7, 1));

  PosTagging::Tagging(nluContext);
}
