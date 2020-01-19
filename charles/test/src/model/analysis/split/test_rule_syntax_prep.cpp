#include <locale>

#include "gtest/gtest.h"

#include "../../../../../src/model/analysis/analysis_clause.h"
#include "../../../../../src/charles.h"

LOGGER_IMPL(xforce::xforce_logger, L"charles")

using namespace xforce;
using namespace xforce::nlu;
using namespace xforce::nlu::charles;

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");
  LOGGER_SYS_INIT(L"../conf/log.conf");

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(testAll, all) {
  const xforce::JsonType* conf = xforce::JsonType::CreateConf("../conf/charles.conf");

  ASSERT_TRUE(Charles::Init(*conf));
  AnalysisClause analysisClause(
      L"按旷课处理",
      EndTags(basic::SyntaxTag::Type::kPp));
  ASSERT_TRUE(analysisClause.Init());
  analysisClause.Process();

  std::cout << basic::AnalysisTracer::Get()->GetReport() << std::endl;
}
