#include "../rule_syntax_prep.h"

namespace xforce { namespace nlu { namespace charles {

RuleSyntaxPrep::RuleSyntaxPrep(size_t idx) :
  idxPrep_(idx) {
}

bool RuleSyntaxPrep::Split(
        const std::shared_ptr<basic::NluContext> &nluContext,
        std::vector<std::shared_ptr<basic::NluContext>> &nluContexts) {
  //basic::Manager::Get().GetGkb().G

  size_t idx=0;
  size_t offsetPrep=0;
  for (auto chunk : nluContext->GetChunks().GetAll()) {
    if (idx<idxPrep_) {
      ++idx;
      continue;
    } else if (idx==idxPrep_) {
      offsetPrep = chunk->GetOffset();
      ++idx;
      continue;
    }

    //after words


    //after poses

    //NP
    if (chunk->GetTag() == basic::SyntaxTag::Type::kAdvp ||
        chunk->GetTag() == basic::SyntaxTag::Type::kU) {
      continue;
    } else if (chunk->GetTag() == basic::SyntaxTag::Type::kNp) {
      basic::Chunk chunk(
              basic::SyntaxTag::Type::kPp,
              offsetPrep,
              chunk.GetOffset() - offsetPrep + chunk.GetLen());

      auto newBranch = nluContext->Clone();
      newBranch->GetChunks().Add(chunk);
      nluContexts.push_back(newBranch);
    }
  }
}

}}}
