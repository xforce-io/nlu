#include "../rule_syntax_cont_np.h"
#include "../forbid_item.h"
#include "../forbid_mgr.h"

namespace xforce { namespace nlu { namespace charles {

RuleSyntaxContNp::RuleSyntaxContNp(size_t offset, size_t len) :
  Rule(offset, len) {}

const char* RuleSyntaxContNp::GetRepr() const {
  std::sprintf(repr_, "ruleSyntaxContNp(%ld|%ld)", offset_, len_);
  return repr_;
}

bool RuleSyntaxContNp::Split(
        const SplitStage &splitStage,
        const std::shared_ptr<basic::NluContext> &nluContext,
        std::vector<std::shared_ptr<basic::NluContext>> &nluContexts) {
  if (!Filter_(nluContext)) {
    return false;
  }

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

void RuleSyntaxContNp::GenForbid(std::vector<ForbidItem> &forbidItems) const {
  ForbidItem forbidItem;
  forbidItem.SetCategoryRule(Rule::kCategoryRuleSyntaxContNp);
  forbidItem.SetOffset(offset_);
  forbidItem.SetLen(len_);
  forbidItems.push_back(forbidItem);
}

bool RuleSyntaxContNp::GlobalCheckForbid(const ForbidItem &forbidItem) const {
  if (forbidItem.GetCategoryRule() == ForbidItem::kCategoryGlobalRuleInterval) {
    return forbidItem.Overlap(offset_, len_);
  }
  return false;
}

bool RuleSyntaxContNp::PreCheckForbid(const ForbidItem &forbidItem) const {
  return forbidItem.GetCategoryRule() == Rule::kCategoryRuleSyntaxContNp &&
      forbidItem.GetOffset() == offset_ &&
      forbidItem.GetLen() == len_;
}

Rule* RuleSyntaxContNp::Clone() {
  return new RuleSyntaxContNp(offset_, len_);
}

bool RuleSyntaxContNp::Filter_(const std::shared_ptr<basic::NluContext> &nluContext) const {
  for (auto &chunk : nluContext->GetChunks().GetAll()) {
    bool hasCommon = false;
    for (auto &tag : chunk->GetTags()) {
      if (!basic::SyntaxTag::Type::IsSpecial(tag)) {
        hasCommon = true;
        break;
      }
    }

    if (!hasCommon) {
      continue;
    }

    if (chunk->Intersect(offset_, len_)) {
      return false;
    }
  }
  return true;
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
    if (newBranch->Add(newChunk)) {
      nluContexts.push_back(newBranch);
      return true;
    }
    return false;
  } else {
    basic::Chunk leftChunk(
            *nluContext,
            basic::SyntaxTag::Type::kNp,
            offset_,
            offset-offset_,
            strategy);

    auto newBranch = Rule::Clone(splitStage, nluContext);
    bool ret0 = newBranch->Add(leftChunk);

    basic::Chunk rightChunk(
            *nluContext,
            basic::SyntaxTag::Type::kNp,
            offset,
            offset_+len_ - offset,
            strategy);


    bool ret1 = newBranch->Add(rightChunk);
    if (ret0 || ret1) {
      nluContexts.push_back(newBranch);
    }
    return ret0 || ret1;
  }
}

}}}
