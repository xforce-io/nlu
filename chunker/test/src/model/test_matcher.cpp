#include <locale>

#include "gtest/gtest.h"

#include "../../../src/model/matcher.h"

LOGGER_IMPL(xforce::xforce_logger, L"chunker")

using namespace xforce;
using namespace xforce::nlu::chunker;

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");
  LOGGER_SYS_INIT(L"../../conf/log.conf");

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(testAll, all) {
  Matcher matcher;
}
