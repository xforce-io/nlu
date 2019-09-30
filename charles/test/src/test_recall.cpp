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
          L"2018年世界女排锦标赛展开第四轮的争夺",
          L"位于B组的中国女排迎战保加利亚队",
          L"但也在本场比赛中遭到了本届世锦赛首局失利",
          //L"中国女排主教练郎平表示",
          L"第一局的失利主要在于自身失误过多",
          L"面对下一个对手意大利队",
          L"中国队会以平常心对待",
          L"作为小组赛第四个对手",
          L"保加利亚队尽管实力并不强",
          L"但却在本场比赛给了中国队强有力的冲击",
          L"谈到第一局的失利",
          L"已经对保加利亚做了充分的准备",
          L"保加利亚也是世界强队之一",
          L"我们也是做了很多的困难准备",
//          L"郎平也分析了首局失利的原因",
          L"第一局比赛失利原因主要在我们自己",
          L"我们自己有太多无谓的失误",
          L"自己的节奏还没有踩上",
          L"队员的心态还有些急躁",
          L"尽管在前两局表现得磕磕绊绊",
          L"但中国女排姑娘们迅速调整了比赛状态",
          L"面对困难局面",
  };

  for (auto &query : wStrQuery) {
    AnalysisClause analysisClause(query);
    ASSERT_TRUE(analysisClause.Init());
    analysisClause.Process();
    assert(analysisClause.GetResults().size() >= 1);
  }
}
