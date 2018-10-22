#include "gtest/gtest.h"
#include "../../../src/data/bigram_dict.h"

LOGGER_IMPL(xforce::xforce_logger, "segmentor")

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(test_all, all) {
    xforce::nlu::BigramDict *bigram_dict = new xforce::nlu::BigramDict();
    ASSERT_TRUE(bigram_dict->Init("../../data/bigramdict.dic"));
    ASSERT_TRUE(bigram_dict->GetFreq("阿", "国内") == 3);
}
