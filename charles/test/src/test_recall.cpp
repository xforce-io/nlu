#include <locale>

#include "gtest/gtest.h"

#include "../../../src/charles.h"
#include "../../../src/model/base_modules.h"
#include "../../../src/model/analysis/analysis_clause.h"

LOGGER_IMPL(xforce::xforce_logger, L"syntax")

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
          L"指导是如何进行人员和战术调整而挽回颓势的呢",
          L"他就这个问题给出了解释",
          L"只要比赛没有结束",
          L"我们就要争取每一分",
          L"下一场比赛",
          L"中国队将面对小组赛实力最为强劲的意大利队",
          L"中国女排面对这个劲敌",
          L"是否会投入额外的准备呢",
          L"对中国队来说哪一场比赛都是重要的",
          L"不能说为了跟意大利比赛",
          L"其余的比赛就不重要",
          L"他在表明备战态度的同时",
          L"也从专业的角度对意大利队进行了分析",
          L"对于意大利这支队伍",
          L"我们今晚是要好好备战的",
          L"这支队伍攻防是非常全面的",
          L"中国女排又有多大的赢球把握呢",
          L"赢球当然是我们的目标",
          L"小米再次发布新的组织架构调整和人事任命",
          L"这是小米上市之后的第六次调整",
          L"他又将亲任中国区总裁",
          L"这是一个极强的信号",
  };

  for (auto &query : wStrQuery) {
    AnalysisClause analysisClause(query, basic::CollectionSyntaxTag(true));
    ASSERT_TRUE(analysisClause.Init());
    analysisClause.Process();
    assert(analysisClause.GetResults().size() >= 1);
  }
}
