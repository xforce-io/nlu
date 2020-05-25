#include "../pattern_set.h"
#include "../../context/context.h"
#include "../../pattern_expr/pattern_expr.h"
#include "../parser/struct_pattern_set.h"
#include "../../refer/refer_manager.h"

namespace xforce { namespace nlu { namespace milkie {

PatternSet::PatternSet(std::shared_ptr<StructPatternSet> structPatternSet) :
    father_(nullptr),
    structPatternSet_(structPatternSet),
    maxLengthPatternStrs_(0),
    patternExprs_(structPatternSet->GetPatternExprs()) {
  patternStrsTrie_ = BuildPatternStrsTrie_(structPatternSet->GetPatternStrs());
}

PatternSet::~PatternSet() {
  XFC_DELETE(patternStrsTrie_)
}

void PatternSet::SetFather(const PatternExpr &patternExpr) {
  if (nullptr != patternExprs_) {
    for (auto &child : *patternExprs_) {
      child->SetFather(patternExpr);
    }
  }
}

void PatternSet::NotifyStorageSpace(const std::wstring &storageSpace) {
  if (nullptr != patternExprs_) {
    for (auto &child : *patternExprs_) {
      child->NotifyStorageSpace(storageSpace);
    }
  }
}

bool PatternSet::MatchPattern(Context &context) {
  if (nullptr != patternStrsTrie_) {
    ssize_t theBegin = -1;
    ssize_t theEnd = -1;
    std::wstring theValue = L"";

    std::wstring matchedSentence;
    if (maxLengthPatternStrs_ < context.GetSentence().GetSentence().length() - context.GetCurPos()) {
      matchedSentence = context.GetSentence().GetSentence().substr(context.GetCurPos(), maxLengthPatternStrs_);
    } else {
      matchedSentence = context.GetSentence().GetSentence().substr(context.GetCurPos());
    }
    StrHelper::ToLowerCase(matchedSentence);

    auto result = patternStrsTrie_->parse_text(matchedSentence);
    for (size_t i=0; i < result.size(); ++i) {
      if (result[i].get_start() == 0) {
        theBegin = result[i].get_start();
        if ((ssize_t)result[i].get_end() > theEnd) {
          theEnd = result[i].get_end();
          theValue = result[i].get_keyword();
        }
      }
    }

    if (0 == theBegin) {
      context.Pass(theEnd - theBegin + 1);
      return true;
    } else {
      return false;
    }
  } else {
    for (auto &patternExpr : *patternExprs_) {
      if (patternExpr->PrefixMatch(context, false)) {
        return true;
      }
    }
    return false;
  }
}

const std::wstring& PatternSet::GetRepr() const { 
  return structPatternSet_->GetStatement(); 
}

const std::wstring* PatternSet::AsStr() const {
  if (nullptr != patternStrsTrie_) {
    if (structPatternSet_->GetPatternStrs()->size() == 1) {
      return &*(structPatternSet_->GetPatternStrs()->begin());
    }
  } else {
    if (patternExprs_->size() == 1) {
      return (*patternExprs_)[0]->AsStr();
    }
  }
  return nullptr;
}

std::pair<std::shared_ptr<PatternSet>, ssize_t> PatternSet::Build(
    const ReferManager &referManager,
    const std::wstring &blockKey,
    const std::wstring &statement) {
  std::shared_ptr<StructPatternSet> structPatternSet = StructPatternSet::Parse(referManager, blockKey, statement);
  if (nullptr == structPatternSet) {
    return std::make_pair(nullptr, -1);
  }
  return std::make_pair(Build(structPatternSet), structPatternSet->GetStatement().length());
}

std::shared_ptr<PatternSet> PatternSet::Build(std::shared_ptr<StructPatternSet> structPatternSet) {
  return std::make_shared<PatternSet>(structPatternSet);
}

}}}
