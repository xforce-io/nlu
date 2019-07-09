#include <segmentor/segmentor.h>
#include "../analysis_clause.h"

#include "../../base_modules.h"

namespace xforce { namespace nlu { namespace charles {

AnalysisClause::AnalysisClause(
        const std::wstring &clause) :
  isMaster_(false),
  nluContext_(std::make_shared<basic::NluContext>(clause)) {}

AnalysisClause::AnalysisClause(
        const std::wstring &clause,
        bool isMaster) :
  isMaster_(isMaster),
  nluContext_(std::make_shared<basic::NluContext>(clause)) {}

bool AnalysisClause::Process(std::vector<std::shared_ptr<AnalysisClause>> &children) {
  xforce::nlu::segmentor::Segmentor::Parse(nluContext_);
  ancestors_.insert(std::make_pair(Stage::kSegment, Clone()));

  xforce::nlu::pos::PosTagging::Tagging(nluContext_);
  ancestors_.insert(std::make_pair(Stage::kPosTag, Clone()));

  xforce::nlu::chunker::Chunker::Parse(nluContext_);
  ancestors_.insert(std::make_pair(Stage::kChunk, Clone()));

  xforce::nlu::syntax::Syntax::Parse(nluContext_);
  ancestors_.insert(std::make_pair(Stage::kSyntax, Clone()));

  if (IsFinished_(*nluContext_)) {
    return true;
  }
}

std::shared_ptr<AnalysisClause> AnalysisClause::Clone() {
  auto cloned = std::make_shared<AnalysisClause>(
          nluContext_->GetQuery(),
          false);
  cloned->nluContext_ = nluContext_->Clone();
  return cloned;
}

void AnalysisClause::Dump(JsonType &jsonType) {
  jsonType["clause"] = *(StrHelper::Wstr2Str(nluContext_->GetQuery()));
  //TODO : Add dump logic
}

bool AnalysisClause::IsFinished_(basic::NluContext &nluContext) {
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
