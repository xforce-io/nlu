#include "../rule_syntax_prep.h"
#include "../split_stage.h"
#include "../../analysis_clause.h"
#include "../forbid_item.h"

namespace xforce { namespace nlu { namespace charles {

RuleSyntaxPrep::RuleSyntaxPrep(
        const std::wstring &prep,
        size_t offset,
        size_t len) :
    Rule(offset, len),
    endTagsForNp_(std::make_shared<basic::CollectionSyntaxTag>(false)),
    endTagsForVp_(std::make_shared<basic::CollectionSyntaxTag>(false)),
    endTagsForPpSub_(std::make_shared<basic::CollectionSyntaxTag>(false)),
    prep_(prep) {
  endTagsForNp_->Add(basic::SyntaxTag::Type::kNp);
  endTagsForVp_->Add(basic::SyntaxTag::Type::kVp);
  endTagsForPpSub_->Add(basic::SyntaxTag::Type::kNp);
  endTagsForPpSub_->Add(basic::SyntaxTag::Type::kV);
  endTagsForPpSub_->Add(basic::SyntaxTag::Type::kVp);

  includeWords_.insert(L"说");
  includeWords_.insert(L"起");
}

const char* RuleSyntaxPrep::GetRepr() const {
  std::sprintf(repr_, "ruleSyntaxPrep(%ld|%ld)", offset_, len_);
  return repr_;
}

void RuleSyntaxPrep::Split(
        const SplitStage &splitStage,
        const std::shared_ptr<basic::NluContext> &nluContext,
        CollectionNluContext &nluContexts) {
  std::vector<const basic::EntryPrep*> entriesPrep;
  basic::Manager::Get().GetGkb().GetGkbPrep().GetEntriesPrep(prep_, entriesPrep);

  bool isJian = false;
  for (auto *entryPrep : entriesPrep) {
    if (entryPrep->TiWei() == basic::EntryPrep::TiWei::kJian) {
      isJian = true;
      break;
    }
  }

  auto iter = nluContext->GetSegments().GetAll().begin();
  std::shared_ptr<basic::Segment> lastSegment;
  while (iter != nluContext->GetSegments().GetAll().end()) {
    auto segment = *iter;
    if (segment->GetOffset() < GetEnd() || GetEnd() == segment->GetBegin()) {
      ++iter;
      continue;
    }

    size_t subChunkTo = segment->GetBegin();
    auto segPos = segment->GetTag();
    auto segWord = segment->GetQuery(nluContext->GetQuery());

    //after words & after poses
    for (auto *entryPrep : entriesPrep) {
      if (entryPrep->IsAfterPos(segPos)) {
        if (segment->GetTag() == basic::PosTag::Type::kU ||
            segment->GetTag() == basic::PosTag::Type::kF ||
            segment->GetTag() == basic::PosTag::Type::kR) {
          subChunkTo = segment->GetEnd();
        }
      } else if (entryPrep->IsAfterWord(segWord)) {
        if (includeWords_.find(segWord) != includeWords_.end()) {
          subChunkTo = segment->GetEnd();
        } else if (L"所" == segWord || L"给" == segWord) {
          auto filter = [](const basic::Chunk &chunk) {
              return chunk.ContainTag(basic::SyntaxTag::Type::kV);
          };

          auto chunk = nluContext->GetChunks().GetFragmentAfter(segment->GetEnd(), filter);
          if (chunk != nullptr) {
            subChunkTo = chunk->GetEnd();
          }
        }
      } else {
        continue;
      }

      AddNewChunk_(
              splitStage,
              nluContext,
              nluContexts,
              subChunkTo - offset_,
              offset_ + len_,
              segment->GetBegin(),
              endTagsForPpSub_,
              lastSegment != nullptr && lastSegment->GetBegin() != GetEnd(),
              910);
      break;
    }
    lastSegment = segment;
    ++iter;
  }

  size_t pos = offset_+len_;
  while (pos < nluContext->GetQuery().length()) {
    auto chunk = nluContext->GetChunks().GetLongFragmentAfter(pos);
    if (nullptr==chunk) {
      break;
    } 
    
    pos += chunk->GetLen();
    if (chunk->GetTag() == basic::SyntaxTag::Type::kAdvp ||
        chunk->GetTag() == basic::SyntaxTag::Type::kU) {
      continue;
    } else if (chunk->ContainTag(basic::SyntaxTag::Type::kNp) ||
               chunk->ContainTag(basic::SyntaxTag::Type::kDt) ||
               chunk->ContainTag(basic::SyntaxTag::Type::kContNp)) {
      AddNewChunk_(
              splitStage,
              nluContext,
              nluContexts,
              chunk->GetEnd() - offset_,
              offset_ + len_,
              chunk->GetEnd(),
              endTagsForNp_,
              false,
              911);
    } else {
      break;
    }
  }

  pos = offset_+len_;
  while (pos < nluContext->GetQuery().length()) {
    auto chunk = nluContext->GetChunks().GetLongFragmentAfter(pos);
    if (nullptr==chunk) {
      break;
    } 
    
    pos += chunk->GetLen();
    if (chunk->GetTag() == basic::SyntaxTag::Type::kPp) {
      continue;
    } else if (isJian && (chunk->ContainTag(basic::SyntaxTag::Type::kV) ||
               chunk->ContainTag(basic::SyntaxTag::Type::kVp))) {
      AddNewChunk_(
              splitStage,
              nluContext,
              nluContexts,
              chunk->GetEnd() - offset_,
              offset_ + len_,
              chunk->GetEnd(),
              endTagsForVp_,
              false,
              912);
    } else {
      break;
    }
  }

  if (!nluContexts.Empty()) {
    nluContexts.Add(nluContext->Clone());
  }
}

void RuleSyntaxPrep::GenForbid(std::vector<ForbidItem> &/*forbidItems*/) const {
/*
  ForbidItem forbidItem;
  forbidItem.SetCategoryRule(GetCategory());
  forbidItem.SetOffset(offset_);
  forbidItem.SetLen(len_);
  forbidItems.push_back(forbidItem);
*/
}

bool RuleSyntaxPrep::PreCheckForbid(const ForbidItem &forbidItem) const {
  return forbidItem.GetCategoryRule() == GetCategory() &&
         forbidItem.GetOffset() == offset_ &&
         forbidItem.GetLen() == len_;
}

Rule* RuleSyntaxPrep::Clone() {
  return new RuleSyntaxPrep(prep_, offset_, len_);
}

bool RuleSyntaxPrep::AddNewChunk_(
        const SplitStage &splitStage,
        const std::shared_ptr<basic::NluContext> &nluContext,
        CollectionNluContext &nluContexts,
        size_t length,
        size_t subChunkFrom,
        size_t subChunkTo,
        std::shared_ptr<basic::CollectionSyntaxTag> &subChunkTags,
        bool phaseCheck,
        uint32_t strategy) {
  basic::Chunk newChunk(
          *nluContext,
          basic::SyntaxTag::Type::kPp,
          offset_,
          length,
          strategy);

  auto newBranch = Rule::Clone(splitStage, nluContext);
  bool ret = newBranch->Add(newChunk);
  if (!ret) {
    return false;
  }

  newBranch->Add(basic::ChunkSep(offset_+length));

  if (phaseCheck) {
    newBranch->AddPhrase(
            subChunkFrom,
            subChunkTo-subChunkFrom,
            subChunkTags,
            strategy);
  } else {
    basic::Chunk subChunk(
            *nluContext,
            subChunkTags->GetTags().front(),
            subChunkFrom,
            subChunkTo-subChunkFrom,
            strategy);
    newBranch->Add(subChunk);
  }

  nluContexts.Add(newBranch);
  return true;
}

}}}
