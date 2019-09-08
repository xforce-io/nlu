#include <segmentor/segmentor.h>
#include "../analysis_clause_branch.h"
#include "../split/split_stage.h"

namespace xforce { namespace nlu { namespace charles {

AnalysisClauseBranch::AnalysisClauseBranch(
        size_t no,
        const basic::NluContext &nluContext,
        const SplitStage &splitStage) :
    no_(no),
    nluContext_(nluContext.Clone()),
    splitStage_(splitStage.Clone()),
    processed_(false),
    end_(false),
    childrenIdx_(0) {
  std::cout << "start of [" << no_ << "]" << std::endl;
  splitStage_->SetBornStage(splitStage_->GetLastStage());
}

AnalysisClauseBranch::~AnalysisClauseBranch() {
  XFC_DELETE(splitStage_)
}

bool AnalysisClauseBranch::Process(
        std::queue<std::shared_ptr<AnalysisClauseBranch>> &branches) {
  if (!processed_) {
    splitStage_->Process(nluContext_);
    processed_ = true;

    if (IsFinished_(*nluContext_)) {
      end_ = true;
      std::cout << "end of [" << no_ << "|1]" << std::endl;
      return true;
    } else if (!nluContext_->GetIsValid()) {
      end_ = true;
      std::cout << "end of [" << no_ << "|2]" << std::endl;
      return false;
    }
  }

  std::vector<std::shared_ptr<basic::NluContext>> nluContexts;
  while (!splitStage_->IsBegin()) {
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

  if (splitStage_->IsBegin()) {
    end_ = true;
    std::cout << "end of [" << no_ << "|3]" << std::endl;
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
      if (tag == basic::SyntaxTag::Type::kStc) {
        return true;
      }
    }
  }
  return false;
}

}}}
