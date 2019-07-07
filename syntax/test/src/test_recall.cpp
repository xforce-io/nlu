#include <locale>

#include "gtest/gtest.h"

#include "../../src/syntax.h"
#include "../../src/model/matcher.h"
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

  std::wstring wStrQuery[] = {
          L"我们自己有太多无谓的失误",
          L"自己的节奏还没有踩上",
          L"面对下一个对手意大利队",
          L"保加利亚队尽管实力并不强",
          L"但却在本场比赛给了中国队强有力的冲击"
  };

  for (auto &query : wStrQuery) {
    auto nluContext = std::make_shared<NluContext>(query);
    Segmentor::Parse(query, nluContext->GetSegments(), nluContext->GetNameEntities());
    PosTagging::Tagging(nluContext);
    Chunker::Parse(nluContext);
    Syntax::Parse(nluContext);

    bool touch = false;
    for (auto &chunk : nluContext->GetChunks().GetAll()) {
      for (auto &tag : chunk->GetTags()) {
        if (tag == SyntaxTag::Type::kStc) {
          touch = true;
        }
      }
    }
    assert(touch);
  }
}
