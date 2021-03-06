#include "../analysis_clause.h"
#include "../analysis_clause_branch.h"
#include "../split/split_rule_mgr.h"

namespace xforce { namespace nlu { namespace charles {

AnalysisClause::AnalysisClause(
        std::shared_ptr<basic::NluContext> nluContext,
        const basic::CollectionSyntaxTag &endTags,
        const std::string &verifyStrategy,
        bool traceEvent) :
    clause_(nluContext),
    endTags_(std::make_shared<basic::CollectionSyntaxTag>(endTags)),
    verifyStrategy_(verifyStrategy),
    traceEvent_(traceEvent),
    master_(nullptr),
    succ_(false) {}

AnalysisClause::AnalysisClause(
        const std::wstring &clause,
        const basic::CollectionSyntaxTag &endTags,
        const std::string &verifyStrategy,
        bool traceEvent) :
    AnalysisClause(
            std::make_shared<basic::NluContext>(clause),
            endTags,
            verifyStrategy,
            traceEvent) {}

AnalysisClause::~AnalysisClause() {
}

bool AnalysisClause::Init() {
  auto splitRuleMgr = new SplitRuleMgr();

  bool ret = splitRuleMgr->Init(*clause_);
  if (!ret) {
    return false;
  }

  auto splitStage = new SplitStage(*splitRuleMgr);
  master_ = std::make_shared<AnalysisClauseBranch>(
          1,
          0,
          *clause_,
          *splitStage,
          *endTags_,
          verifyStrategy_,
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
    jsonType["depth"] = master_->GetDepth();
    master_->GetNluContext()->Dump(jsonType["ctx"], nullptr);
    basic::AnalysisTracer::Get()->AddEvent(
            master_->GetNluContext()->GetQuery(),
            jsonType);
  }

  if (ret) {
    finished_.push_back(master_);
    results_.push_back(master_);
    succ_ = true;
    return true;
  } else if (master_->GetEnd() && branches_.empty()) {
    finished_.push_back(master_);
    return false;
  }

  succ_ = false;
  while (!branches_.empty()) {
    auto branch = branches_.front();
    branches_.pop();

    allBranches_.insert(std::make_pair(branch->GetNo(), branch));

    if (branch->GetDepth() < 10) {
      ret = branch->Process(branches_);
    } else {
      branch->SetEnd(true);
      ret = false;
    }

    if (ret) {
      succ_ = true;
      finished_.push_back(branch);
      results_.push_back(branch);
      theEndTag_ = branch->GetTheEndTag();
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
      jsonType["depth"] = branch->GetDepth();
      auto father = GetFather(branch);
      branch->GetNluContext()->Dump(
              jsonType["diff"],
              nullptr!=father ? &(*father->GetNluContext()) : nullptr);
      branch->GetNluContext()->Dump(jsonType["ctx"], nullptr);
      jsonType["isValid"] = branch->GetNluContext()->GetIsValid();
      basic::AnalysisTracer::Get()->AddEvent(
              branch->GetNluContext()->GetQuery(),
              jsonType);
    }
  }
  return succ_;
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
