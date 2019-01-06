#include "../pattern_set.h"
#include "../../context/context.h"
#include "../../pattern_expr/pattern_expr.h"

namespace xforce { namespace nlu { namespace milkie {

PatternSet::PatternSet(const StructPatternSet &structPatternSet) :
    patternExprs_(*structPatternSet.GetPatternExprs()) {
  patternStrsTrie_ = BuildPatternStrsTrie_(structPatternSet.GetPatternStrs());
}

bool PatternSet::MatchPattern(Context &context) {
  if (nullptr != patternStrsTrie_) {
    int theBegin = -1;
    int theEnd = -1;
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
        if (result[i].get_end() > theEnd) {
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
    for (auto &patternExpr : patternExprs_) {
      if (patternExpr->MatchPattern(context, false)) {
        return true;
      }
    }
    return false;
  }
}

const std::wstring* PatternSet::AsStr() const {
  if (nullptr != patternStrsTrie_) {
    if (structPatternSet_->GetPatternStrs()->size() == 1) {
      return &*(structPatternSet_->GetPatternStrs()->begin());
    }
  } else {
    if (patternExprs_.size() == 1) {
      return patternExprs_[0]->AsStr();
    }
  }
  return nullptr;
}

std::pair<std::shared_ptr<PatternSet>, ssize_t> PatternSet::Build(
    const std::wstring &blockKey, 
    const std::wstring &statement) {
  std::shared_ptr<StructPatternSet> structPatternSet = structPatternSet::Parse(blockKey, statement);
  if (nullptr == structPatternSet.get()) {
    return std::make_pair(nullptr, -1);
  }
  return std::make_pair(Build(*structPatternSet), structPatternSet->GetStatement().length());
}

std::shared_ptr<PatternSet> PatternSet::Build(const StructPatternSet &structPatternSet) {
  return std::make_shared<PatternSet>(structPatternSet);
}

}}}
