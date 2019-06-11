#include <locale>

#include "gtest/gtest.h"
#include "../../src/pos_tagging.h"
#include "../../src/conf/conf.h"
#include "basic/model/segment.h"
#include "basic/model/name_entity.h"
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
  try {
    const xforce::JsonType* conf = xforce::JsonType::CreateConf("../conf/pos.conf");
    ASSERT_TRUE(Basic::Init((*conf)["basic"]));
    ASSERT_TRUE(Segmentor::Init((*conf)["segmentor"], (*conf)["ner"]));
    ASSERT_TRUE(PosTagging::Init((*conf)["pos"]));

    std::wstring wStrQuery = L"单根主缆拉力高达9万吨";
    Segment::Set segments(wStrQuery);
    NameEntity::Set nameEntities(wStrQuery);

    Segmentor::Parse(wStrQuery, segments, nameEntities);

    auto nluContext = std::make_shared<basic::NluContext>(wStrQuery);
    nluContext->SetSegments(segments);

    PosTagging::Tagging(nluContext);

    xforce::JsonType jsonToDump;
    nluContext->GetSegments().Dump(jsonToDump);

    std::stringstream ss;
    jsonToDump.DumpJson(ss);
    std::cout << ss.str() << std::endl;
  } catch(char *str) {
    std::cout << str << std::endl;
  }
}
