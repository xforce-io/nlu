#include <locale>

#include "gtest/gtest.h"

#include "../../../src/charles.h"
#include "../../../src/model/base_modules.h"
#include "../../../src/model/analysis/split/split_stage.h"
#include "../../../src/model/analysis/analysis_clause.h"
#include "../../../src/model/analysis/analysis_clause_branch.h"

LOGGER_IMPL(xforce::xforce_logger, L"charles")

using namespace xforce;
using namespace xforce::nlu;
using namespace xforce::nlu::charles;

int main(int /*argc*/, char** /*argv*/) {
  setlocale(LC_ALL, "");
  LOGGER_SYS_INIT(L"../conf/log.conf");

  const xforce::JsonType* conf = xforce::JsonType::CreateConf("../conf/charles.conf");

  assert(Charles::Init(*conf));
  AnalysisClause analysisClause(L"他是如何进行人员和战术调整而挽回颓势的呢",basic::CollectionSyntaxTag(true));
  assert(analysisClause.Init());
  bool ret = analysisClause.Process();
  std::cout << basic::AnalysisTracer::Get()->GetReport() << std::endl;
  assert(ret);

  return 0;
}
