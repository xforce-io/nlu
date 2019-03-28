#include "gtest/gtest.h"
#include "../../../src/model/graph/graph.h"
#include "../../../src/segmentor.h"

LOGGER_IMPL(xforce::xforce_logger, "segmentor")

using namespace xforce;
using namespace xforce::nlu::basic;
using namespace xforce::nlu::segmentor;

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

bool Check(const std::string &query, const std::vector<std::string> &segStrs);

TEST(test_all, all) {
  setlocale(LC_ALL, "");

  const xforce::JsonType* conf = xforce::JsonType::CreateConf("conf/segmentor.conf");
  ASSERT_TRUE(Segmentor::Init((*conf)["segmentor"], (*conf)["ner"]));

  std::string filepath = "../../data/regressionCases";

  FILE *fp = fopen(filepath.c_str(), "r");
  ASSERT_TRUE(fp != nullptr);

  char buf[4096];
  char *line = fgets(buf, sizeof(buf), fp);
  std::vector<std::string> results;
  while (nullptr!=line) {
    if (buf[strlen(buf) - 1] == '\n') {
      buf[strlen(buf) - 1] = '\0';
    }

    if (buf[strlen(buf) - 1] == '\r') {
      buf[strlen(buf) - 1] = '\0';
    }

    results.clear();
    if (strlen(buf) > 0) {
      StrHelper::SplitStr(buf, ' ', results);
      ASSERT_TRUE(results.size() == 2);

      std::string query = results[0];
      std::vector<std::string> segStrs;
      StrHelper::SplitStr(results[1], '/', segStrs);
      ASSERT_TRUE(Check(query, segStrs));
    }
    line = fgets(buf, sizeof(buf), fp);
  }
  fclose(fp);

  Segmentor::Tini();
  XFC_DELETE(conf)
}

bool Check(const std::string &query, const std::vector<std::string> &segStrs) {
  std::cout << "test[" << query << "]" << std::endl;

  std::wstring wStrQuery;
  assert(StrHelper::Str2Wstr(query, wStrQuery));

  Segments segments;
  Graph::NameEntities nameEntities;

  Graph *graph = new Graph(wStrQuery);
  graph->Process(segments, nameEntities);

  if (segments.size() != segStrs.size() + 1) {
    return false;
  }

  for (size_t i=0; i < segStrs.size(); ++i) {
    std::wstring wstr;
    assert(StrHelper::Str2Wstr(segStrs[i], wstr));
    if (wstr.length() + (size_t)segments[i].GetOffset() != (size_t)segments[i+1].GetOffset()) {
      return false;
    }
  }

  XFC_DELETE(graph)
  return true;
}
