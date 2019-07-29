#include "../analysis_clause.h"
#include "../analysis_clause_branch.h"

namespace xforce { namespace nlu { namespace charles {

AnalysisClause::AnalysisClause(const std::wstring &clause) :
  nluContextSplit_(nullptr),
  clause_(clause),
  master_(nullptr) {}

AnalysisClause::~AnalysisClause() {
  XFC_DELETE(nluContextSplit_)
}

bool AnalysisClause::Init() {
  nluContextSplit_ = new NluContextSplit();
  bool ret = nluContextSplit_->Init();
  master_ = std::make_shared<AnalysisClauseBranch>(*nluContextSplit_, 1, clause_);
  return ret;
}

bool AnalysisClause::Process() {
  bool ret = master_->Process(branches_);
  if (ret) {
    finished_.push_back(master_);
    results_.push_back(master_);
    return true;
  } else if (master_->GetEnd()) {
    finished_.push_back(master_);
    return false;
  }

  bool succ = false;
  while (!branches_.empty()) {
    auto branch = branches_.front();
    branches_.pop();

    ret = branch->Process(branches_);
    if (ret) {
      succ = true;
      finished_.push_back(branch);
      results_.push_back(branch);
    } else if (branch->GetEnd()) {
      finished_.push_back(branch);
    }
  }
  return succ;
}

void AnalysisClause::Dump(JsonType &jsonType) {
  UNUSE(jsonType)
}

}}}
