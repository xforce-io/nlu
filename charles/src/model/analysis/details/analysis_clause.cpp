#include "../analysis_clause.h"
#include "../analysis_clause_branch.h"
#include "../split/split_rule_mgr.h"

namespace xforce { namespace nlu { namespace charles {

AnalysisClause::AnalysisClause(
        const std::wstring &clause,
        basic::SyntaxTag::Type::Val endTag,
        bool traceEvent) :
    clause_(std::make_shared<basic::NluContext>(clause)),
    endTag_(endTag),
    traceEvent_(traceEvent),
    master_(nullptr) {}

AnalysisClause::~AnalysisClause() {
}

bool AnalysisClause::Init() {
  SplitRuleMgr *splitRuleMgr = new SplitRuleMgr();

  bool ret = splitRuleMgr->Init(*clause_);
  if (!ret) {
    return false;
  }

  auto splitStage = new SplitStage(*splitRuleMgr);
  master_ = std::make_shared<AnalysisClauseBranch>(
          1,
          *clause_,
          *splitStage,
          endTag_,
          traceEvent_);
  XFC_DELETE(splitStage);
  allBranches_.insert(std::make_pair(master_->GetNo(), master_));
  return ret;
}

bool AnalysisClause::Process() {
  bool ret = master_->Process(branches_);
  if (master_->GetEnd() && traceEvent_) {
    JsonType jsonType;
    jsonType["name"] = "branch_end";
    jsonType["no"] = master_->GetNo();
    master_->GetNluContext()->Dump(jsonType["ctx"], nullptr);
    basic::AnalysisTracer::Get()->AddEvent(jsonType);
  }

  if (ret) {
    finished_.push_back(master_);
    results_.push_back(master_);
    return true;
  } else if (master_->GetEnd() && branches_.empty()) {
    finished_.push_back(master_);
    return false;
  }

  bool succ = false;
  while (!branches_.empty()) {
    auto branch = branches_.front();
    branches_.pop();

    allBranches_.insert(std::make_pair(branch->GetNo(), branch));

    ret = branch->Process(branches_);
    if (ret) {
      succ = true;
      finished_.push_back(branch);
      results_.push_back(branch);
    } else {
      if (branch->GetEnd()) {
        finished_.push_back(branch);
      } else {
        branches_.push(branch);
      }
    }

    if (branch->GetEnd() && traceEvent_) {
      JsonType jsonType;
      jsonType["name"] = "branch_end";
      jsonType["no"] = branch->GetNo();
      auto father = GetFather(branch);
      branch->GetNluContext()->Dump(
              jsonType["diff"],
              nullptr!=father ? &(*father->GetNluContext()) : nullptr);
      branch->GetNluContext()->Dump(jsonType["ctx"], nullptr);
      jsonType["isValid"] = branch->GetNluContext()->GetIsValid();
      basic::AnalysisTracer::Get()->AddEvent(jsonType);
    }
  }
  return succ;
}

AnalysisClause::Branch AnalysisClause::GetFather(Branch &branch) {
  if (branch->GetNo() <= 1) {
    return nullptr;
  }
  auto iter = allBranches_.find(branch->GetNoFather());
  return allBranches_.end() != iter ? iter->second : nullptr;
}

void AnalysisClause::Dump(JsonType &jsonType) {
  UNUSE(jsonType)
}

}}}
