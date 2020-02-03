#include <segmentor/segmentor.h>
#include "../analysis_clause_branch.h"
#include "../split/split_stage.h"
#include "../analysis_clause.h"

namespace xforce { namespace nlu { namespace charles {

AnalysisClauseBranch::AnalysisClauseBranch(
        ssize_t no,
        const basic::NluContext &nluContext,
        const SplitStage &splitStage,
        const basic::CollectionSyntaxTag &endTags,
        const std::string &verifyStrategy,
        bool traceEvent) :
    no_(endTags.IsStc() ? abs(no): -abs(no)),
    nluContext_(nluContext.Clone()),
    splitStage_(splitStage.Clone()),
    endTags_(endTags),
    verifyStrategy_(verifyStrategy),
    traceEvent_(traceEvent),
    processed_(false),
    end_(false),
    childrenIdx_(0) {
  splitStage_->SetBornStage(splitStage_->GetLastStage());
}

AnalysisClauseBranch::~AnalysisClauseBranch() {
  XFC_DELETE(splitStage_)
}

bool AnalysisClauseBranch::Process(
        std::queue<std::shared_ptr<AnalysisClauseBranch>> &branches) {
  if (!processed_) {
    int verifySubBranch = VerifySubBranches_();
    if (traceEvent_) {
      JsonType jsonType;
      jsonType["name"] = "branch_init";
      jsonType["no"] = no_;
      jsonType["born"] = splitStage_->GetBornStage();
      if (splitStage_->GetLastRule() != nullptr) {
        jsonType["rule"] = splitStage_->GetLastRule()->GetRepr();
      }
      jsonType["verifySubBranch"] = verifySubBranch;
      if (!endTags_.IsStc()) {
        jsonType["endTag"] = basic::CollectionSyntaxTag::Str(endTags_);
      }
      jsonType["verifyStrategy"] = verifyStrategy_;
      basic::AnalysisTracer::Get()->AddEvent(
              nluContext_->GetQuery(),
              jsonType);
    }

    if (1==verifySubBranch) {
      nluContext_->SetIsValid(false);
      end_ = true;
      return false;
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

  CollectionNluContext nluContexts;
  while (!splitStage_->IsEnd()) {
    nluContexts.Clear();

    splitStage_->Split(nluContext_, nluContexts);
    if (!nluContexts.Empty()) {
      break;
    }
  }

  for (auto const &nluContext : nluContexts.Get()) {
    auto absVal = abs(no_) * 100 + childrenIdx_;
    auto child = std::make_shared<AnalysisClauseBranch>(
            no_>=0 ? absVal : -absVal,
            *nluContext,
            *splitStage_,
            endTags_,
            verifyStrategy_,
            traceEvent_);
    branches.push(child);
    children_.push_back(child);
    ++childrenIdx_;
  }
  ++childrenIdx_;

  if (!nluContexts.Empty()) {
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
    if (chunk->GetOffset() != 0 ||
        chunk->GetLen() != nluContext.GetQuery().length()) {
      continue;
    }

    for (auto &tag : chunk->GetTags()) {
      if (endTags_.ContainTag(tag)) {
        theEndTag_ = tag;
        return true;
      }
    }
  }
  return false;
}

int AnalysisClauseBranch::VerifySubBranches_() {
  bool touched = false;
  for (auto &phrase : nluContext_->GetPhrases()) {
    std::wstring subQuery = phrase.GetNluContext()->GetQuery();
    auto clauseToVerify = std::make_shared<AnalysisClause>(
            subQuery,
            basic::CollectionSyntaxTag(chunk->GetTag()),
            chunk->GetVerifyStrategy(),
            true);
    bool ret = clauseToVerify->Init();
    if (!ret) {
      FATAL("fail_init_sub_query[" << subQuery << "]");
      return 1;
    }

    if (!clauseToVerify->Process()) {
      return 1;
    }
  }
  return touched ? 0 : -1;
}

}}}
