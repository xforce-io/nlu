#include "../rule_syntax_prep.h"
#include "../split_stage.h"
#include "../../analysis_clause.h"
#include "../forbid_item.h"

namespace xforce { namespace nlu { namespace charles {

RuleSyntaxPrep::RuleSyntaxPrep(
        const std::wstring &prep,
        size_t offset,
        size_t len) :
  prep_(prep),
  offsetPrep_(offset),
  lenPrep_(len) {
}

bool RuleSyntaxPrep::Split(
        const SplitStage &splitStage,
        const std::shared_ptr<basic::NluContext> &nluContext,
        std::vector<std::shared_ptr<basic::NluContext>> &nluContexts) {
  std::vector<const basic::EntryPrep*> entriesPrep;
  basic::Manager::Get().GetGkb().GetGkbPrep().GetEntriesPrep(prep_, entriesPrep);

  bool touched=false;
  for (auto &segment : nluContext->GetSegments().GetAll()) {
    if (segment->GetOffset() < offsetPrep_+lenPrep_) {
      continue;
    }

    //after words & after poses
    for (auto *entryPrep : entriesPrep) {
      if (entryPrep->IsAfterWord(segment->GetQuery(nluContext->GetQuery())) ||
          entryPrep->IsAfterPos(segment->GetTag())) {
        if (AddNewChunk_(
                splitStage,
                nluContext,
                nluContexts,
                segment->GetEnd() - offsetPrep_,
                offsetPrep_+lenPrep_,
                segment->GetBegin(),
                basic::SyntaxTag::Type::kUndef,
                910)) {
          touched = true;
        }
        break;
      }
    }
  }

  for (auto &chunk : nluContext->GetChunks().GetAll()) {
    if (chunk->GetOffset() < offsetPrep_+lenPrep_) {
      continue;
    }

    //NP
    if (chunk->GetTag() == basic::SyntaxTag::Type::kAdvp ||
        chunk->GetTag() == basic::SyntaxTag::Type::kU) {
      continue;
    } else if (chunk->GetTag() == basic::SyntaxTag::Type::kNp ||
        chunk->GetTag() == basic::SyntaxTag::Type::kContNp) {
      if (AddNewChunk_(
              splitStage,
              nluContext,
              nluContexts,
              chunk->GetEnd() - offsetPrep_,
              offsetPrep_+lenPrep_,
              chunk->GetEnd(),
              basic::SyntaxTag::Type::kNp,
              911)) {
        touched = true;
      }
    }
  }
  return touched;
}

bool RuleSyntaxPrep::GenForbid(ForbidItem &forbidItem) const {
  forbidItem.SetCategoryRule(Rule::kCategoryRuleSyntaxPrep);
  forbidItem.SetOffset(forbidItem.GetOffset());
  forbidItem.SetLen(forbidItem.GetLen());
  return true;
}

bool RuleSyntaxPrep::PreCheckForbid(const ForbidItem &forbidItem) const {
  return forbidItem.GetCategoryRule() == Rule::kCategoryRuleSyntaxPrep &&
      forbidItem.GetOffset() == offsetPrep_ &&
      forbidItem.GetLen() == lenPrep_;
}

Rule* RuleSyntaxPrep::Clone() {
  return new RuleSyntaxPrep(prep_, offsetPrep_, lenPrep_);
}

bool RuleSyntaxPrep::AddNewChunk_(
        const SplitStage &splitStage,
        const std::shared_ptr<basic::NluContext> &nluContext,
        std::vector<std::shared_ptr<basic::NluContext>> &nluContexts,
        size_t length,
        size_t subChunkFrom,
        size_t subChunkTo,
        basic::SyntaxTag::Type::Val subChunkTag,
        uint32_t strategy) {
  basic::Chunk newChunk(
          *nluContext,
          basic::SyntaxTag::Type::kPp,
          offsetPrep_,
          length,
          strategy);

  auto newBranch = Rule::Clone(splitStage, nluContext);
  bool ret = newBranch->GetChunks().Add(newChunk);
  if (!ret) {
    return false;
  }

  if (basic::SyntaxTag::Type::kUndef != subChunkTag) {
    basic::Chunk subChunk(
            *nluContext,
            subChunkTag,
            subChunkFrom,
            subChunkTo-subChunkFrom,
            strategy);
    newBranch->GetChunks().Add(subChunk);
  } else {
    std::wstring subStr = nluContext->GetQuery().substr(
                    subChunkFrom,
                    subChunkTo-subChunkFrom);
    AnalysisClause analysisClause(subStr);
    ret = analysisClause.Init();
    if (!ret) {
      ERROR("fail_init_analysis_clause[" << subStr << "]");
      return false;
    }

    ret = analysisClause.Process();
    if (!ret) {
      return false;
    }

    newBranch->AddPhrase(
            subChunkFrom,
            subChunkTo,
            analysisClause.GetClause());
  }
  nluContexts.push_back(newBranch);
  return true;
}

}}}
