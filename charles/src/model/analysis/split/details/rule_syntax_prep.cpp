#include "../rule_syntax_prep.h"
#include "../split_stage.h"

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
                nluContext,
                nluContexts,
                segment->GetEnd() - offsetPrep_,
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
              nluContext,
              nluContexts,
              chunk->GetEnd() - offsetPrep_,
              911)) {
        touched = true;
      }
    }
  }
  return touched;
}

Rule* RuleSyntaxPrep::Clone() {
  return new RuleSyntaxPrep(prep_, offsetPrep_, lenPrep_);
}

bool RuleSyntaxPrep::AddNewChunk_(
        const SplitStage &splitStage,
        const std::shared_ptr<basic::NluContext> &nluContext,
        std::vector<std::shared_ptr<basic::NluContext>> &nluContexts,
        size_t length,
        uint32_t strategy) {
  basic::Chunk newChunk(
          *nluContext,
          basic::SyntaxTag::Type::kPp,
          offsetPrep_,
          length,
          strategy);

  auto newBranch = Rule::Clone(splitStage, nluContext);
  bool ret = newBranch->GetChunks().Add(newChunk);
  nluContexts.push_back(newBranch);
  return ret;
}

}}}
