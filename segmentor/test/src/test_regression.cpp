#include "gtest/gtest.h"
#include "../../../src/model/graph/graph.h"
#include "../../../src/segmentor.h"

LOGGER_IMPL(xforce::xforce_logger, L"segmentor")

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

  auto wStrQuery = StrHelper::Str2Wstr(query);
  assert(wStrQuery != nullptr);

  Segment::Set segments(*wStrQuery);
  NameEntity::Set nameEntities(*wStrQuery);

  Graph *graph = new Graph(*wStrQuery);
  graph->Process(segments, nameEntities);

  if (segments.Size() != segStrs.size()) {
    return false;
  }

  auto cur = segments.Begin();
  if (cur != segments.End()) {
    auto next = cur;
    ++next;
    size_t idx = 0;
    while (next != segments.End()) {
      auto wstr = StrHelper::Str2Wstr(segStrs[idx]);
      assert(wstr != nullptr);
      if (wstr->length() + (size_t)(*cur)->GetOffset() != (size_t)(*next)->GetOffset()) {
        return false;
      }

      cur = next;
      ++next;
      ++idx;
    }
  }

  XFC_DELETE(graph)
  return true;
}
