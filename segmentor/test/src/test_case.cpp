#include <locale>

#include "gtest/gtest.h"
#include "../../../src/model/graph/graph.h"
#include "../../../src/segmentor.h"

LOGGER_IMPL(xforce::xforce_logger, "segmentor")

using namespace xforce;
using namespace xforce::nlu::basic;
using namespace xforce::nlu::segmentor;

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");
  std::wcout << L"还有什么更好的办法吗";

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

bool Check(const std::string &query, const std::vector<std::string> &segments);

TEST(test_all, all) {
  const xforce::JsonType* conf = xforce::JsonType::CreateConf("conf/segmentor.conf");
  ASSERT_TRUE(Segmentor::Init((*conf)["segmentor"], (*conf)["ner"]));

  Segments segments;
  Graph::NameEntities nameEntities;

  std::wstring wStrQuery = L"周杰伦、刘亦菲和王凯的关系很好";
  Graph *graph = new Graph(wStrQuery);
  graph->Process(segments, nameEntities);

  for (size_t i=0; i < segments.size(); ++i) {
    std::wcout << wStrQuery.substr(segments[i].GetOffset(), segments[i].GetLen()) << std::endl;
  }

  XFC_DELETE(graph)

  Segmentor::Tini();
  XFC_DELETE(conf)
}
