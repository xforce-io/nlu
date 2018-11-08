#include "gtest/gtest.h"
#include "../../../src/data/bigram_dict.h"
#include "../../../src/segmentor.h"

LOGGER_IMPL(xforce::xforce_logger, "segmentor")

using namespace xforce::nlu;

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(test_all, all) {
    ASSERT_TRUE(Segmentor::Init("conf/segmentor.conf"));

    xforce::nlu::BigramDict *bigram_dict = new xforce::nlu::BigramDict();
    ASSERT_TRUE(bigram_dict->Init("../../data/bigramdict.dic"));
    ASSERT_TRUE(bigram_dict->GetFreq(L"阿", L"国内") == 3);
}
