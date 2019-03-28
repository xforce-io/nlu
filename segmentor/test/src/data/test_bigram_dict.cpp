#include "gtest/gtest.h"
#include "../../../src/data/bigram_dict.h"
#include "../../../src/segmentor.h"

using namespace xforce::nlu::segmentor;

namespace xforce {
LOGGER_IMPL(xforce_logger, "segmentor")
}

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");
  std::wcout << L"还有什么更好的办法吗";

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(test_all, all) {
  const xforce::JsonType* conf = xforce::JsonType::CreateConf("conf/segmentor.conf");
  ASSERT_TRUE(Segmentor::Init((*conf)["segmentor"], (*conf)["ner"]));

  auto bigram_dict = new xforce::nlu::segmentor::BigramDict();
  ASSERT_TRUE(bigram_dict->Init("../../data/bigramdict.dic"));
  ASSERT_TRUE(bigram_dict->GetFreq(L"阿", L"国内") == 3);

  XFC_DELETE(conf)
}
