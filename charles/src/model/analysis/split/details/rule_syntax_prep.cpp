#include "../rule_syntax_prep.h"

namespace xforce { namespace nlu { namespace charles {

RuleSyntaxPrep::RuleSyntaxPrep(size_t offset) :
  offsetPrep_(offset) {
}

bool RuleSyntaxPrep::Split(
        const std::shared_ptr<basic::NluContext> &nluContext,
        std::vector<std::shared_ptr<basic::NluContext>> &nluContexts) {
  std::vector<const basic::EntryPrep*> entriesPrep;
  basic::Manager::Get().GetGkb().GetGkbPrep().GetEntriesPrep(
          nluContext->GetQuery(),
          entriesPrep);

  bool touched=false;
  for (auto &segment : nluContext->GetSegments().GetAll()) {
    if (segment->GetOffset() < offsetPrep_) {
      continue;
    }

    //after words & after poses
    for (auto *entryPrep : entriesPrep) {
      if (entryPrep->IsAfterWord(segment->GetQuery(nluContext->GetQuery())) ||
          entryPrep->IsAfterPos(segment->GetTag())) {
        AddNewChunk_(
                nluContext,
                nluContexts,
                segment->GetOffset() - offsetPrep_ + segment->GetLen());
        touched = true;
        break;
      }
    }
  }

  for (auto &chunk : nluContext->GetChunks().GetAll()) {
    if (chunk->GetOffset() <= offsetPrep_) {
      continue;
    }

    //NP
    if (chunk->GetTag() == basic::SyntaxTag::Type::kAdvp ||
        chunk->GetTag() == basic::SyntaxTag::Type::kU) {
      continue;
    } else if (chunk->GetTag() == basic::SyntaxTag::Type::kNp) {
      AddNewChunk_(
              nluContext,
              nluContexts,
              chunk->GetOffset() - offsetPrep_ + chunk->GetLen());
      touched = true;
    }
  }
  return touched;
}

Rule* RuleSyntaxPrep::Clone() {
  return new RuleSyntaxPrep(offsetPrep_);
}

void RuleSyntaxPrep::AddNewChunk_(
        const std::shared_ptr<basic::NluContext> &nluContext,
        std::vector<std::shared_ptr<basic::NluContext>> &nluContexts,
        size_t length) {
  basic::Chunk newChunk(
          basic::SyntaxTag::Type::kPp,
          offsetPrep_,
          length);

  auto newBranch = nluContext->Clone();
  newBranch->GetChunks().Add(newChunk);
  nluContexts.push_back(newBranch);
}

}}}
