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
/*
  assert(Charles::Init(*conf));
  AnalysisClause analysisClause(L"他是如何进行人员和战术调整而挽回颓势的呢",basic::CollectionSyntaxTag(true));
  assert(analysisClause.Init());
  bool ret = analysisClause.Process();
  std::cout << basic::AnalysisTracer::Get()->GetReport() << std::endl;
  assert(ret);
  */
  std::wstring q = L"2018年世界女排锦标赛展开第四轮的争夺";
  basic::NluContext nluContext(q);
  basic::FragmentSet<basic::Chunk> fset(q);
  fset.Add(std::make_shared<basic::Chunk>(nluContext, basic::SyntaxTag::Type::kUndef, 0, 5));
  fset.Add(std::make_shared<basic::Chunk>(nluContext, basic::SyntaxTag::Type::kUndef,14, 3));
  fset.Add(std::make_shared<basic::Chunk>(nluContext, basic::SyntaxTag::Type::kUndef, 5, 9));
  fset.Add(std::make_shared<basic::Chunk>(nluContext, basic::SyntaxTag::Type::kUndef,17, 1));
  fset.Add(std::make_shared<basic::Chunk>(nluContext, basic::SyntaxTag::Type::kUndef,18, 2));
  fset.Add(std::make_shared<basic::Chunk>(nluContext, basic::SyntaxTag::Type::kUndef, 0, 5));
  fset.Add(std::make_shared<basic::Chunk>(nluContext, basic::SyntaxTag::Type::kUndef,14, 3));
  fset.Add(std::make_shared<basic::Chunk>(nluContext, basic::SyntaxTag::Type::kUndef,14, 6));
  fset.Add(std::make_shared<basic::Chunk>(nluContext, basic::SyntaxTag::Type::kUndef, 5,15));
  fset.Add(std::make_shared<basic::Chunk>(nluContext, basic::SyntaxTag::Type::kUndef, 5,15));
  fset.Add(std::make_shared<basic::Chunk>(nluContext, basic::SyntaxTag::Type::kUndef, 5,15));
  fset.Add(std::make_shared<basic::Chunk>(nluContext, basic::SyntaxTag::Type::kUndef, 5,15));
  bool ret = fset.Add(std::make_shared<basic::Chunk>(nluContext, basic::SyntaxTag::Type::kUndef, 5,15));
  std::cout << ret << std::endl;
  return 0;
}
