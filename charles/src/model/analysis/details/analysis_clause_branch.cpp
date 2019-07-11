#include <segmentor/segmentor.h>
#include "../analysis_clause_branch.h"

namespace xforce { namespace nlu { namespace charles {

AnalysisClauseBranch::AnalysisClauseBranch(const std::wstring &clause) :
  nluContext_(std::make_shared<basic::NluContext>(clause)) {}

AnalysisClauseBranch::AnalysisClauseBranch(const basic::NluContext &nluContext) :
  nluContext_(nluContext.Clone()) {}

bool AnalysisClauseBranch::Process(
        std::queue<std::shared_ptr<AnalysisClauseBranch>> &children) {
  segmentor::Segmentor::Parse(nluContext_);
  pos::PosTagging::Tagging(nluContext_);
  chunker::Chunker::Parse(nluContext_);
  syntax::Syntax::Parse(nluContext_);

  if (IsFinished_(*nluContext_)) {
    return true;
  }

  std::vector<std::shared_ptr<basic::NluContext>> nluContexts;
  nluContext_->Split(nluContexts);
  for (auto nluContext : nluContexts) {
    children.push(std::make_shared<AnalysisClauseBranch>(nluContext));
  }
  return false;
}

std::shared_ptr<AnalysisClauseBranch> AnalysisClauseBranch::Clone() const {
  return std::make_shared<AnalysisClauseBranch>(*nluContext_);
}

void AnalysisClauseBranch::Dump(JsonType &jsonType) {

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