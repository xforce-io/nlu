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
    prep_(prep) {
  endTagsForNp_.Add(basic::SyntaxTag::Type::kNp);
  endTagsForVp_.Add(basic::SyntaxTag::Type::kV);
  endTagsForVp_.Add(basic::SyntaxTag::Type::kVp);
  endTagsForPpSub_.Add(basic::SyntaxTag::Type::kNp);
  endTagsForPpSub_.Add(basic::SyntaxTag::Type::kV);
  endTagsForPpSub_.Add(basic::SyntaxTag::Type::kVp);

  includeWords_.insert(L"说");
  includeWords_.insert(L"来说");
  includeWords_.insert(L"来看");
  includeWords_.insert(L"之外");
  includeWords_.insert(L"而外");
  includeWords_.insert(L"以外");
  includeWords_.insert(L"以后");
  includeWords_.insert(L"以来");
  includeWords_.insert(L"起");
  includeWords_.insert(L"外");
}

const char* RuleSyntaxPrep::GetRepr() const {
  std::sprintf(repr_, "ruleSyntaxPrep(%ld|%ld)", offset_, len_);
  return repr_;
}

bool RuleSyntaxPrep::Split(
        const SplitStage &splitStage,
        const std::shared_ptr<basic::NluContext> &nluContext,
        std::vector<std::shared_ptr<basic::NluContext>> &nluContexts) {
  std::vector<const basic::EntryPrep*> entriesPrep;
  basic::Manager::Get().GetGkb().GetGkbPrep().GetEntriesPrep(prep_, entriesPrep);

  bool isJian = false;
  for (auto *entryPrep : entriesPrep) {
    if (entryPrep->TiWei() == basic::EntryPrep::TiWei::kJian) {
      isJian = true;
      break;
    }
  }

  bool touched=false;
  for (auto &segment : nluContext->GetSegments().GetAll()) {
    if (segment->GetOffset() < GetEnd() || GetEnd() == segment->GetBegin()) {
      continue;
    }

    auto segPos = segment->GetTag();
    auto segWord = segment->GetQuery(nluContext->GetQuery());

    //after words & after poses
    for (auto *entryPrep : entriesPrep) {
      bool includeBoundary = false;
      if (entryPrep->IsAfterPos(segPos)) {
        if (segment->GetTag() == basic::PosTag::Type::kU ||
            segment->GetTag() == basic::PosTag::Type::kF ||
            segment->GetTag() == basic::PosTag::Type::kR) {
          includeBoundary = true;
        }
      } else if (entryPrep->IsAfterWord(segWord)) {
        if (includeWords_.find(segWord) != includeWords_.end()) {
          includeBoundary = true;
        } else if (L"所" == segWord || L"给" == segWord) {
          auto chunk = nluContext->GetChunks().GetFragmentAfter(segment->GetEnd());
          if (chunk != nullptr && chunk->ContainTag())
        }
      } else {
        continue;
      }

      if (AddNewChunk_(
              splitStage,
              nluContext,
              nluContexts,
              segment->GetEnd() - offset_,
              offset_ + len_,
              segment->GetBegin(),
              endTagsForPpSub_,
              910)) {
        touched = true;
      }
      break;
    }
  }

  for (auto &chunk : nluContext->GetChunks().GetAll()) {
    if (chunk->GetOffset() < offset_ + len_) {
      continue;
    }

    //NP
    if (chunk->GetTag() == basic::SyntaxTag::Type::kAdvp ||
        chunk->GetTag() == basic::SyntaxTag::Type::kU) {
      continue;
    } else if (chunk->ContainTag(basic::SyntaxTag::Type::kNp) ||
        chunk->ContainTag(basic::SyntaxTag::Type::kContNp)) {
      if (AddNewChunk_(
              splitStage,
              nluContext,
              nluContexts,
              chunk->GetEnd() - offset_,
              offset_ + len_,
              chunk->GetEnd(),
              endTagsForNp_,
              911)) {
        touched = true;
      }
    } else if (isJian &&
        (chunk->ContainTag(basic::SyntaxTag::Type::kV) ||
        chunk->ContainTag(basic::SyntaxTag::Type::kVp))) {
      if (AddNewChunk_(
              splitStage,
              nluContext,
              nluContexts,
              chunk->GetEnd() - offset_,
              offset_ + len_,
              chunk->GetEnd(),
              endTagsForVp_,
              912)) {
        touched = true;
      }
    } else {
      break;
    }
  }
  return touched;
}

void RuleSyntaxPrep::GenForbid(std::vector<ForbidItem> &forbidItems) const {
  ForbidItem forbidItem;
  forbidItem.SetCategoryRule(GetCategory());
  forbidItem.SetOffset(offset_);
  forbidItem.SetLen(len_);
  forbidItems.push_back(forbidItem);
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
        std::vector<std::shared_ptr<basic::NluContext>> &nluContexts,
        size_t length,
        size_t subChunkFrom,
        size_t subChunkTo,
        const EndTags &subChunkTags,
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

  std::wstring subStr = nluContext->GetQuery().substr(
                  subChunkFrom,
                  subChunkTo-subChunkFrom);
  AnalysisClause analysisClause(
          subStr,
          subChunkTags,
          GetRepr());
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

  nluContexts.push_back(newBranch);
  return true;
}

}}}
