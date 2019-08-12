#include "../analysis_clause.h"
#include "../analysis_clause_branch.h"
#include "../split/split_rule_mgr.h"

namespace xforce { namespace nlu { namespace charles {

AnalysisClause::AnalysisClause(const std::wstring &clause) :
    clause_(std::make_shared<basic::NluContext>(clause)),
    splitRuleMgr_(nullptr),
    master_(nullptr) {}

AnalysisClause::~AnalysisClause() {
  XFC_DELETE(splitRuleMgr_)
}

bool AnalysisClause::Init() {
  splitRuleMgr_ = new SplitRuleMgr();

  bool ret = splitRuleMgr_->Init(*clause_);
  if (!ret) {
    return false;
  }

  auto splitStage = new SplitStage(*splitRuleMgr_);
  master_ = std::make_shared<AnalysisClauseBranch>(1, *clause_, *splitStage);
  XFC_DELETE(splitStage);
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
