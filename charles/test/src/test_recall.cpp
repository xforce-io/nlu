#include <locale>

#include "gtest/gtest.h"

#include "../../../src/charles.h"
#include "../../../src/model/base_modules.h"
#include "../../../src/model/analysis/analysis_clause.h"

LOGGER_IMPL(xforce::xforce_logger, L"syntax")

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

  std::wstring wStrQuery[] = {
          L"我们自己有太多无谓的失误",
          L"自己的节奏还没有踩上",
          L"面对下一个对手意大利队",
          L"保加利亚队尽管实力并不强",
          L"但却在本场比赛给了中国队强有力的冲击",
          L"我们也是做了很多的困难准备",
          L"郎平也分析了首局失利的原因",
          L"第一局比赛失利原因主要在我们自己",
          L"队员的心态还有些急躁",
  };

  for (auto &query : wStrQuery) {
    AnalysisClause analysisClause(query);
    ASSERT_TRUE(analysisClause.Init());
    analysisClause.Process();
    assert(analysisClause.GetResults().size() == 1);
  }
}
