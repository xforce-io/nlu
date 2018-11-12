#include "gtest/gtest.h"
#include "../../../src/data/word_dict.h"
#include "../../../src/data/nature_dict.h"
#include "../../../src/data/manager.h"
#include "../../../src/model/core_dict_item.h"
#include "../../../src/segmentor.h"

LOGGER_IMPL(xforce::xforce_logger, "segmentor")

using namespace xforce::nlu::segmentor;

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

void initNatureDict() {
  NatureDict *natureDict = new NatureDict();
  ASSERT_TRUE(natureDict->Init("../../data/nature/nature.map"));
  Manager::SetNatureDict(*natureDict);
}

TEST(test_all, all) {
  LOGGER_SYS_INIT("../conf/log.conf")

  ASSERT_TRUE(Segmentor::Init("conf/segmentor.conf"));

  initNatureDict();

  WordDict *wordDict = new WordDict();
  std::vector<std::string> wordDictPaths;
  wordDictPaths.push_back("../../data/word/core.dic");
  ASSERT_TRUE(wordDict->Init(wordDictPaths));

  std::vector<const CoreDictItem*> results;
  wordDict->PrefixMatch(L"中国人民银行", results);
  std::cout << results.size() << std::endl;
  for (auto iter = results.begin(); iter != results.end(); ++iter) {
    std::wcout << (*iter)->GetName() << std::endl;
  }
  delete wordDict;
}
