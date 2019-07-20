#include <segmentor/segmentor.h>
#include "../analysis_clause_branch.h"
#include "../nlu_context_split.h"

namespace xforce { namespace nlu { namespace charles {

AnalysisClauseBranch::AnalysisClauseBranch(const std::wstring &clause) :
  nluContext_(std::make_shared<basic::NluContext>(clause)),
  splitStage_(basic::Stage::kEnd),
  processed_(false),
  end_(false) {}

AnalysisClauseBranch::AnalysisClauseBranch(const basic::NluContext &nluContext) :
  nluContext_(nluContext.Clone()),
  splitStage_(basic::Stage::kSyntax),
  processed_(false),
  end_(false) {}

bool AnalysisClauseBranch::Process(
        std::queue<std::shared_ptr<AnalysisClauseBranch>> &branches) {
  if (!AllChildrenEnd_()) {
    return false;
  }

  if (!processed_) {
    segmentor::Segmentor::Parse(nluContext_);
    pos::PosTagging::Tagging(nluContext_);
    chunker::Chunker::Parse(nluContext_);
    syntax::Syntax::Parse(nluContext_);
    processed_ = true;

    if (IsFinished_(*nluContext_)) {
      end_ = true;
      return true;
    }
  }

  std::vector<std::shared_ptr<basic::NluContext>> nluContexts;
  while (basic::Stage::kNone != splitStage_) {
      bool ret = NluContextSplit::Split(*nluContext_, nluContexts, splitStage_);
      splitStage_ = basic::Stage::GetPrev(splitStage_);
      if (!ret) {
        continue;
      }
  }

  for (auto nluContext : nluContexts) {
    auto child = std::make_shared<AnalysisClauseBranch>(*nluContext);
    branches.push(child);
    children_.push_back(child);
  }

  if (basic::Stage::kNone != splitStage_) {
    branches.push(std::make_shared<AnalysisClauseBranch>(*this));
  } else {
    end_ = true;
  }
  return false;
}

std::shared_ptr<AnalysisClauseBranch> AnalysisClauseBranch::Clone() const {
  return std::make_shared<AnalysisClauseBranch>(*nluContext_);
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
