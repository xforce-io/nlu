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
  const xforce::JsonType* conf = xforce::JsonType::CreateConf("../conf/chunker.conf");

  Matcher matcher;
  assert(matcher.Init());

  std::wstring wStrQuery = L"谈到第一局的失利";
  NluContext nluContext(wStrQuery);
  Segmentor::Parse(wStrQuery, nluContext.GetSegments(), nluContext.GetN)

  matcher.Match(nluContext);
}
