#include <segmentor/segmentor.h>
#include "../analysis_clause_branch.h"
#include "../nlu_context_split.h"

namespace xforce { namespace nlu { namespace charles {

AnalysisClauseBranch::AnalysisClauseBranch(
        NluContextSplit &nluContextSplit,
        size_t no,
        const std::wstring &clause) :
  nluContextSplit_(&nluContextSplit),
  no_(no),
  nluContext_(std::make_shared<basic::NluContext>(clause)),
  bornStage_(basic::Stage::kNone),
  curStage_(basic::Stage::kSyntax),
  processed_(false),
  end_(false) {}

AnalysisClauseBranch::AnalysisClauseBranch(
        NluContextSplit &nluContextSplit,
        size_t no,
        const basic::NluContext &nluContext) :
  nluContextSplit_(&nluContextSplit),
  no_(no),
  nluContext_(nluContext.Clone()),
  bornStage_(basic::Stage::kNone),
  curStage_(basic::Stage::kSyntax),
  processed_(false),
  end_(false) {}

bool AnalysisClauseBranch::Process(
        std::queue<std::shared_ptr<AnalysisClauseBranch>> &branches) {
  if (!AllChildrenEnd_()) {
    return false;
  }

  if (!processed_) {
    if (bornStage_ <= basic::Stage::kSegment) {
      segmentor::Segmentor::Parse(nluContext_);
      if (bornStage_ <= basic::Stage::kPosTag) {
        pos::PosTagging::Tagging(nluContext_);
        if (bornStage_ <= basic::Stage::kChunk) {
          chunker::Chunker::Parse(nluContext_);
          if (bornStage_ <= basic::Stage::kSyntax) {
            syntax::Syntax::Parse(nluContext_);
          }
        }
      }
    }
    processed_ = true;

    if (IsFinished_(*nluContext_)) {
      end_ = true;
      return true;
    }
  }

  std::vector<std::shared_ptr<basic::NluContext>> nluContexts;
  basic::Stage::Val lastStage = basic::Stage::kEnd;
  while (basic::Stage::kNone != curStage_) {
    nluContexts.clear();

    bool ret = nluContextSplit_->Split(nluContext_, nluContexts, curStage_);
    lastStage = curStage_;
    curStage_ = basic::Stage::GetPrev(curStage_);
    if (ret) {
      break;
    }
  }

  size_t idx=0;
  for (auto nluContext : nluContexts) {
    auto child = std::make_shared<AnalysisClauseBranch>(
            *nluContextSplit_,
            no_ * 10 + idx,
            *nluContext);
    child->bornStage_ = lastStage;
    child->curStage_ = curStage_;
    branches.push(child);
    children_.push_back(child);
    ++idx;
  }

  if (basic::Stage::kNone != curStage_) {
    auto copy = std::make_shared<AnalysisClauseBranch>(*nluContextSplit_, no_, *nluContext_);
    copy->bornStage_ = bornStage_;
    copy->curStage_ = curStage_;
    copy->processed_ = processed_;
    branches.push(copy);
  } else {
    end_ = true;
  }
  return false;
}

std::shared_ptr<AnalysisClauseBranch> AnalysisClauseBranch::Clone() const {
  return std::make_shared<AnalysisClauseBranch>(*nluContextSplit_, no_, *nluContext_);
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
