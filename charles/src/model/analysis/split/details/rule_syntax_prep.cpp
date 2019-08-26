#include "../rule_syntax_prep.h"

namespace xforce { namespace nlu { namespace charles {

RuleSyntaxPrep::RuleSyntaxPrep(size_t offset, size_t len) :
  offsetPrep_(offset),
  lenPrep_(len) {
}

bool RuleSyntaxPrep::Split(
        const std::shared_ptr<basic::NluContext> &nluContext,
        std::vector<std::shared_ptr<basic::NluContext>> &nluContexts) {
  std::wstring prep = nluContext->GetQuery().substr(offsetPrep_, lenPrep_);
  std::vector<const basic::EntryPrep*> entriesPrep;
  basic::Manager::Get().GetGkb().GetGkbPrep().GetEntriesPrep(prep, entriesPrep);

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
  return new RuleSyntaxPrep(offsetPrep_, lenPrep_);
}

bool RuleSyntaxPrep::AddNewChunk_(
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

  auto newBranch = nluContext->Clone();
  bool ret = newBranch->GetChunks().Add(newChunk);
  nluContexts.push_back(newBranch);
  return ret;
}

}}}
