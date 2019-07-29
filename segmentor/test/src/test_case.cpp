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
  std::wcout << L"我也不知道为什么要这一句" << std::endl;

  LOGGER_SYS_INIT(L"../conf/log.conf");

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

bool Check(const std::string &query, const std::vector<std::string> &segments);

TEST(test_all, all) {
  const xforce::JsonType* conf = xforce::JsonType::CreateConf("conf/segmentor.conf");
  ASSERT_TRUE(Segmentor::Init((*conf)["segmentor"], (*conf)["ner"]));

  std::wstring wStrQuery = L"中国女排在赛后";
  Segment::Set segments(wStrQuery);
  NameEntity::Set nameEntities(wStrQuery);

  Graph *graph = new Graph(wStrQuery);
  graph->Process(segments, nameEntities);

  xforce::JsonType jsonToDump;
  segments.Dump(jsonToDump);

  std::stringstream ss;
  jsonToDump.DumpJson(ss);
  std::cout << ss.str() << std::endl;
  for (auto &segment : segments.GetAll()) {
    std::wcout << wStrQuery.substr(segment->GetOffset(), segment->GetLen()) << std::endl;
  }

  XFC_DELETE(graph)

  Segmentor::Tini();
  XFC_DELETE(conf)
}
