#include <locale>

#include "gtest/gtest.h"
#include "../../../src/model/graph/graph.h"
#include "../../../src/segmentor.h"

LOGGER_IMPL(xforce::xforce_logger, L"segmentor")

using namespace xforce::nlu;
using namespace xforce::nlu::basic;
using namespace xforce::nlu::segmentor;

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");
  LOGGER_SYS_INIT(L"../conf/log.conf");

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

bool Check(const std::string &query, const std::vector<std::string> &segments);

TEST(test_all, all) {
  const xforce::JsonType* conf = xforce::JsonType::CreateConf("conf/segmentor.conf");
  ASSERT_TRUE(Segmentor::Init((*conf)["segmentor"], (*conf)["ner"]));

  std::wstring wStrQuery = L"五峰山特大桥是继南京长江大桥、在建沪通长江大桥之后长江江苏段的第三座公铁两用大桥";

  Segment::Set segments(wStrQuery);
  NameEntity::Set nameEntities(wStrQuery);

  Graph *graph = new Graph(wStrQuery);
  graph->Process(segments, nameEntities);

  for (size_t i=0; i < segments.Size(); ++i) {
    std::wcout << wStrQuery.substr(segments[i]->GetOffset(), segments[i]->GetLen()) << std::endl;
  }

  XFC_DELETE(graph)

  Segmentor::Tini();
  XFC_DELETE(conf)
}
