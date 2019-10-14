#include <segmentor/segmentor.h>
#include "../analysis_clause_branch.h"
#include "../split/split_stage.h"
#include "../analysis_clause.h"
#include "../sub_branch.h"

namespace xforce { namespace nlu { namespace charles {

AnalysisClauseBranch::AnalysisClauseBranch(
        size_t no,
        const basic::NluContext &nluContext,
        const SplitStage &splitStage,
        basic::SyntaxTag::Type::Val endTag) :
    no_(no),
    nluContext_(nluContext.Clone()),
    splitStage_(splitStage.Clone()),
    endTag_(endTag),
    processed_(false),
    end_(false),
    childrenIdx_(0) {
  splitStage_->SetBornStage(splitStage_->GetLastStage());
}

AnalysisClauseBranch::~AnalysisClauseBranch() {
  for (SubBranch *subBranch : subBranches_) {
    delete subBranch;
  }
  XFC_DELETE(splitStage_)
}

bool AnalysisClauseBranch::Process(
        std::queue<std::shared_ptr<AnalysisClauseBranch>> &branches) {
  if (!processed_) {
    JsonType jsonType;
    jsonType["name"] = "branch_init";
    jsonType["no"] = no_;
    jsonType["born"] = splitStage_->GetBornStage();
    if (splitStage_->GetLastRule() != nullptr) {
      jsonType["rule"] = splitStage_->GetLastRule()->GetRepr();
    }
    basic::AnalysisTracer::Get()->AddEvent(jsonType);

    if (!VerifySubBranches_()) {
      end_ = true;
      return false;
    }

    if (no_ == 10101) {
      int a = 0;
    }

    splitStage_->Process(nluContext_);
    processed_ = true;

    if (IsFinished_(*nluContext_)) {
      end_ = true;
      return true;
    } else if (!nluContext_->GetIsValid()) {
      end_ = true;
      return false;
    }
  }

  std::vector<std::shared_ptr<basic::NluContext>> nluContexts;
  while (!splitStage_->IsEnd()) {
    nluContexts.clear();

    bool ret = splitStage_->Split(nluContext_, nluContexts);
    if (ret) {
      break;
    }
  }

  for (auto const &nluContext : nluContexts) {
    auto child = std::make_shared<AnalysisClauseBranch>(
            no_ * 100 + childrenIdx_,
            *nluContext,
            *splitStage_);
    branches.push(child);
    children_.push_back(child);
    ++childrenIdx_;
  }
  ++childrenIdx_;

  if (!nluContexts.empty()) {
    end_ = true;
    return false;
  }

  if (splitStage_->IsEnd()) {
    end_ = true;
  }
  return false;
}

void AnalysisClauseBranch::Dump(JsonType &jsonType) {
  UNUSE(jsonType)
}

bool AnalysisClauseBranch::AllChildrenEnd_() {
  for (auto &child : children_) {
    if (!child->end_) {
      return false;
    }
  }
  return true;
}

bool AnalysisClauseBranch::IsFinished_(basic::NluContext &nluContext) {
  for (auto &chunk : nluContext.GetChunks().GetAll()) {
    for (auto &tag : chunk->GetTags()) {
      if (tag == endTag_) {
        return true;
      }
    }
  }
  return false;
}

bool AnalysisClauseBranch::VerifySubBranches_() {
  for (auto &chunk : nluContext_->GetChunks().GetAll()) {
    if (!chunk->GetNeedToVerify()) {
      continue;
    }

    std::wstring subQuery = chunk->GetQuery(nluContext_->GetQuery());
    auto clauseToVerify = std::make_shared<AnalysisClause>(subQuery);
    bool ret = clauseToVerify->Init();
    if (!ret) {
      FATAL("fail_init_sub_query[" << subQuery << "]");
      return false;
    }

    if (clauseToVerify->Process()) {
      auto subBranch = new SubBranch(
              *chunk,
              clauseToVerify);
      subBranches_.push_back(subBranch);
    } else {
      return false;
    }
  }
  return true;
}

}}}
