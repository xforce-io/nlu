#include "gtest/gtest.h"
#include "../../../src/model/graph/graph.h"
#include "../../../src/segmentor.h"

LOGGER_IMPL(xforce::xforce_logger, "segmentor")

using namespace xforce;
using namespace xforce::nlu::segmentor;

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

bool Check(const std::string &query, const std::vector<std::string> &segments);

TEST(test_all, all) {
  setlocale(LC_ALL, "");

  const xforce::JsonType* conf = xforce::JsonType::CreateConf("conf/segmentor.conf");
  ASSERT_TRUE(Segmentor::Init((*conf)["segmentor"], (*conf)["ner"]));

  std::string filepath = "../../data/regressionCases";

  FILE *fp = fopen(filepath.c_str(), "r");
  ASSERT_TRUE(fp != NULL);

  char buf[4096];
  char *line = fgets(buf, sizeof(buf), fp);
  std::vector<std::string> results;
  while (NULL!=line) {
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
      std::vector<std::string> segments;
      StrHelper::SplitStr(results[1], '/', segments);
      ASSERT_TRUE(Check(query, segments));
    }
    line = fgets(buf, sizeof(buf), fp);
  }
  fclose(fp);

  Segmentor::Tini();
  XFC_DELETE(conf)
}

bool Check(const std::string &query, const std::vector<std::string> &segments) {
  std::cout << "test[" << query << "]" << std::endl;

  std::wstring wStrQuery;
  assert(StrHelper::Str2Wstr(query, wStrQuery));

  Graph::Offsets offsets;
  Graph::NameEntities nameEntities;

  Graph *graph = new Graph(wStrQuery);
  graph->Process(offsets, nameEntities);

  if (offsets.size() != segments.size()) {
    return false;
  }

  for (size_t i=0; i < segments.size()-1; ++i) {
    std::wstring wstr;
    assert(StrHelper::Str2Wstr(segments[i], wstr));
    if (wstr.length() + (size_t)offsets[i] != (size_t)offsets[i+1]) {
      return false;
    }
  }

  XFC_DELETE(graph)
  return true;
}
