#include "../analysis_clause.h"

namespace xforce { namespace nlu { namespace charles {

AnalysisClause::AnalysisClause(const std::wstring &clause) :
  master_(std::make_shared<AnalysisClauseBranch>(clause)) {}

bool AnalysisClause::Process() {
  bool ret = master_->Process(branches_);
  if (ret) {
    results_.push_back(master_);
    return true;
  }

  bool succ = false;
  while (!branches_.empty()) {
    auto branch = branches_.front();
    branches_.pop();

    ret = branch->Process(branches_);
    if (ret) {
      succ = true;
      results_.push_back(branch);
    }
  }
  return succ;
}

void AnalysisClause::Dump(JsonType &jsonType) {
  UNUSE(jsonType)
}

}}}
