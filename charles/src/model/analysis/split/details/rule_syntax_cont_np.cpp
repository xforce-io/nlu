#include "../rule_syntax_cont_np.h"
#include "../forbid_item.h"

namespace xforce { namespace nlu { namespace charles {

RuleSyntaxContNp::RuleSyntaxContNp(size_t offset, size_t len) :
  offset_(offset),
  len_(len) {}

bool RuleSyntaxContNp::Split(
        const SplitStage &splitStage,
        const std::shared_ptr<basic::NluContext> &nluContext,
        std::vector<std::shared_ptr<basic::NluContext>> &nluContexts) {
  bool touched = false;
  for (auto &segment : nluContext->GetSegments().GetAll()) {
    if (segment->GetEnd() <= offset_ ||
        segment->GetEnd() == offset_+len_ ||
        segment->GetOffset() >= offset_+len_) {
      continue;
    }

    if (segment->GetTag() == basic::PosTag::Type::kN ||
        segment->GetTag() == basic::PosTag::Type::kVn ||
        segment->GetTag() == basic::PosTag::Type::kR) {
      if (AddNewChunk_(
              splitStage,
              nluContext,
              nluContexts,
              segment->GetEnd(),
              940)) {
        touched = true;
      }
    }
  }

  if (AddNewChunk_(
          splitStage,
          nluContext,
          nluContexts,
          offset_,
          941)) {
    touched = true;
  }
  return touched;
}

bool RuleSyntaxContNp::GenForbid(ForbidItem &forbidItem) const {
  forbidItem.SetCategoryRule(Rule::kCategoryRuleSyntaxContNp);
  forbidItem.SetOffset(offset_);
  forbidItem.SetLen(len_);
  return true;
}

bool RuleSyntaxContNp::PreCheckForbid(const ForbidItem &forbidItem) const {
  return forbidItem.GetCategoryRule() == Rule::kCategoryRuleSyntaxContNp &&
      forbidItem.GetOffset() == offset_ &&
      forbidItem.GetLen() == len_;
}

Rule* RuleSyntaxContNp::Clone() {
  return new RuleSyntaxContNp(offset_, len_);
}

bool RuleSyntaxContNp::AddNewChunk_(
        const SplitStage &splitStage,
        const std::shared_ptr<basic::NluContext> &nluContext,
        std::vector<std::shared_ptr<basic::NluContext>> &nluContexts,
        size_t offset,
        uint32_t strategy) {
  if (offset == offset_) {
    basic::Chunk newChunk(
            *nluContext,
            basic::SyntaxTag::Type::kNp,
            offset_,
            len_,
            strategy);

    auto newBranch = Rule::Clone(splitStage, nluContext);
    return newBranch->GetChunks().Add(newChunk);
  } else {
    basic::Chunk leftChunk(
            *nluContext,
            basic::SyntaxTag::Type::kNp,
            offset_,
            offset-offset_,
            strategy);

    auto newBranch = Rule::Clone(splitStage, nluContext);
    bool ret0 = newBranch->GetChunks().Add(leftChunk);
    if (ret0) {
      nluContexts.push_back(newBranch);
    }

    basic::Chunk rightChunk(
            *nluContext,
            basic::SyntaxTag::Type::kNp,
            offset,
            offset_+len_ - offset,
            strategy);


    newBranch = Rule::Clone(splitStage, nluContext);
    bool ret1 = newBranch->GetChunks().Add(rightChunk);
    if (ret0) {
      nluContexts.push_back(newBranch);
    }
    return ret0 || ret1;
  }
}

}}}
