#include <locale>

#include "gtest/gtest.h"

#include "../../../src/syntax.h"
#include "../../../src/model/matcher.h"
#include "basic/model/segment.h"
#include "basic/model/name_entity.h"
#include "basic/basic.h"
#include "segmentor/segmentor.h"
#include "pos_tagging/pos_tagging.h"
#include "chunker/chunker.h"

LOGGER_IMPL(xforce::xforce_logger, L"syntax")

using namespace xforce;
using namespace xforce::nlu::basic;
using namespace xforce::nlu::segmentor;
using namespace xforce::nlu::pos;
using namespace xforce::nlu::chunker;
using namespace xforce::nlu::syntax;

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");
  LOGGER_SYS_INIT(L"../conf/log.conf");

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(testAll, all) {
  const xforce::JsonType* conf = xforce::JsonType::CreateConf("../conf/syntax.conf");
  ASSERT_TRUE(Basic::Init((*conf)["basic"]));
  ASSERT_TRUE(Segmentor::Init((*conf)["segmentor"], (*conf)["ner"]));
  ASSERT_TRUE(PosTagging::Init((*conf)["pos"]));
  ASSERT_TRUE(Chunker::Init((*conf)["chunker"]));
  ASSERT_TRUE(Syntax::Init((*conf)["syntax"]));

  std::wstring wStrQuery = L"谈到第一局的失利";
  auto nluContext = std::make_shared<NluContext>(wStrQuery);
  Segmentor::Parse(wStrQuery, nluContext->GetSegments(), nluContext->GetNameEntities());
  PosTagging::Tagging(nluContext);
  Chunker::Parse(nluContext);

  xforce::JsonType jsonToDump;
  nluContext->GetSegments().Dump(jsonToDump);
  nluContext->GetChunkSeps().Dump(jsonToDump);

  std::stringstream ss;
  jsonToDump.DumpJson(ss);
  std::cout << ss.str() << std::endl;

  Syntax::Parse(nluContext);

  nluContext->GetChunks().Dump(jsonToDump);

  ss.str("");
  jsonToDump.DumpJson(ss);
  std::cout << ss.str() << std::endl;
}
