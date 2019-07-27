#include <locale>

#include "gtest/gtest.h"

#include "../../../src/charles.h"
#include "../../../src/model/base_modules.h"
#include "../../../src/model/analysis/analysis_clause.h"

LOGGER_IMPL(xforce::xforce_logger, L"charles")

using namespace xforce;
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
  AnalysisClause analysisClause(L"第一局比赛失利原因主要在我们自己");
  ASSERT_TRUE(analysisClause.Init());
  analysisClause.Process();

  std::cout << analysisClause.GetFinished().size() << std::endl;

  std::string repr;
  for (auto result : analysisClause.GetFinished()) {
    std::cout << "no[" << result->GetNo() << "] ";
    std::cout << "born[" << result->GetBornStage() << "] ";
    result->GetNluContext()->Dump(repr);
    std::cout << "result[" << repr << "]" << std::endl;
  }
}
