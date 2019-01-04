#include "../pattern_expr.h"
#include "../parser/struct_pattern_expr.h"
#include "../../pattern/pattern.h"
#include "../../pattern_set/pattern_set.h"
#include "../../../../conf/conf.h"

namespace xforce { namespace nlu { namespace milkie {

std::unordered_set<char> PatternExpr::invalidLeadPosForWildcard_ = PatternExpr::CreateInvalidLeadPosForWildcard();
std::unordered_set<std::string> PatternExpr::invalidFullPosForWildcard_ = PatternExpr::CreateInvalidFullPosForWildcard();

PatternExpr::PatternExpr(
    std::shared_ptr<Pattern> pattern,
    std::shared_ptr<PatternSet> patternSet,
    const std::wstring *wildcardName,
    std::shared_ptr<StructPatternExpr> structPatternExpr) {
  if (nullptr == pattern ||
      nullptr == patternSet ||
      nullptr == wildcardName) {
    return;
  }

  wildcardName_ = new std::wstring(*wildcardName);

  if (structPatternExpr->GetPattern() != nullptr) {
    pattern_ = structPatternExpr_->GetPattern();
    return;
  } else if (structPatternExpr->GetPatternSet() != nullptr) {
    patternSet_ = structPatternExpr_->GetPatternSet();
    return;
  }

  if (structPatternExpr->GetItems() != nullptr) {
    items_ = *(structPatternExpr_->GetItems());
  }

  if (nullptr != structPatternExpr_) {
    storage_ = structPatternExpr_->GetStorage();
    repeatPattern_ = structPatternExpr_->GetCategoryPatternExpr();
  }
}

PatternExpr::~PatternExpr() {
  XFC_DELETE(wildcardName_)
}

std::wstring PatternExpr::GetRepr() const {
  std::wstringstream ss;
  if (nullptr != pattern_) {
    ss << "Pattern(" << pattern_->GetRepr() << ")";
  } else if (nullptr != patternSet_) {
    ss << "PatternSet(" << patternSet_->GetRepr() << ")";
  } else if (nullptr != wildcardName_) {
    ss << "Wildcard(" << wildcardName_ << ")";
  } else {
    ss << "PatternExpr(" << structPatternExpr_->GetStatement() << ")";
  }
  return ss.str();
}

bool PatternExpr::MatchPattern(Context &context, bool singleton) {
  ssize_t startIdx = context.GetCurPos();
  if (context.End()) {
    if (repeatPattern_ == CategoryPatternExpr::kZeroOrOnce ||
        repeatPattern_ == CategoryPatternExpr::kZeroOrMore) {
      DebugMatch_(context, startIdx, true);
      return true;
    }

    if (nullptr != pattern_ || nullptr != patternSet_) {
      DebugMatch_(context, startIdx, false);
      return false;
    }

    for (auto &item : items_) {
      if (item->repeatPattern_ != CategoryPatternExpr::kZeroOrOnce &&
          item->repeatPattern_ != CategoryPatternExpr::kZeroOrMore) {
        DebugMatch_(context, startIdx, false);
        return false;
      }
    }
    DebugMatch_(context, startIdx, true);
    return true;
  }

  context.StartMatch();
  if (nullptr != pattern_) {
    bool ret = pattern_->MatchPattern(context);
    if (ret) {
      StopMatch(true, context, singleton);
    } else {
      StopMatch(false, context, singleton);
    }
    DebugMatch_(context, startIdx, ret);
    return ret;
  } else if (nullptr != patternSet_) {
    bool ret = patternSet_->MatchPattern(context);
    if (ret) {
      StopMatch(true, context, singleton);
    } else {
      StopMatch(false, context, singleton);
    }
    DebugMatch_(context, startIdx, ret);
    return ret;
  }

  bool exit = false;
  size_t numMatches = 0;
  do {
    exit = false;
    ssize_t ret = MatchFromIdx(0, context);
    if (ret>0) {
      exit = true;
    } else if (ret<0) {
      bool tmpRet = MatchForWildcard(context, -ret);
      context.StopMatch(tmpRet);
      DebugMatch_(context, startIdx, tmpRet);
      return tmpRet;
    }

    if (!exit) {
      ++numMatches;
      if (1 == numMatches &&
          (CategoryPatternExpr::kZeroOrOnce == repeatPattern_ ||
          CategoryPatternExpr::kOnce == repeatPattern_)) {
        exit = true;
      }
    }
  } while (!exit);

  if (0 == numMatches) {
    bool ret = (CategoryPatternExpr::kZeroOrOnce == repeatPattern_ ||
            CategoryPatternExpr::kZeroOrMore == repeatPattern_);
    context.StopMatch(ret);
    DebugMatch_(context, startIdx, ret);
    return ret;
  }

  StopMatch(true, context, singleton);
  DebugMatch_(context, startIdx, true);
  return true;
}

ssize_t PatternExpr::MatchFromIdx(ssize_t fromIdx, Context &context) {
  ssize_t idx = fromIdx;
  while (idx < items_.size()) {
    auto patternExpr = items_[idx];
    if (nullptr != patternExpr.AsWildcard()) {
      return -(idx+1);
    }

    bool mark = false;
    if (items_.size() == 1) {
      mark = true;
    }

    if (!patternExpr->MatchPattern(context, mark)) {
      return 1;
    }
    ++idx;
  }
  return 0;
}

bool PatternExpr::MatchForWildcard(Context &context, ssize_t itemIdx) {
  ssize_t offset = context.GetCurPos();
  bool exitInner = false;

  auto wordposAtPos = context.GetSentence().GetFeatureSegmentAtOffset(offset);
  if (nullptr != wordposAtPos) {
    auto fullWordpos = basic::Pos::Str(wordposAtPos->GetPos());
    auto leadingWordpos = fullWordpos[0];
    if (PatternExpr::invalidLeadPosForWildcard_.find(leadingWordpos) != PatternExpr::invalidLeadPosForWildcard_.end() ||
        PatternExpr::invalidFullPosForWildcard_.find(fullWordpos) != PatternExpr::invalidFullPosForWildcard_.end()) {
      exitInner = true;
    }
  }

  ssize_t oldCurPos = context.GetCurPos();
  while (!exitInner) {
    context.StartMatch(offset);
    ssize_t retInner = MatchFromIdx(itemIdx, context);
    if (0 == retInner &&
        oldCurPos != offset &&
        context.GetCurPos() == context.GetSentence().GetSentence().length()) {
      context.SetStorageStr(
              items_[itemIdx-1].AsWildcard(),
              context.GetSentence().GetSentence().substr(oldCurPos, offset-oldCurPos));
      context.StopMatch(true);
      context.SetStorage(storage_, *(context.GetStoragePattern()));
    }

    if (offset == context.Length()) {
      exitInner = true;
    }
    context.StopMatch(false);
    ++offset;
  }
  return false;
}

void PatternExpr::StopMatch(bool succ, Context &context, bool singleton) {
  if (succ) {
    if (nullptr != storage_) {
      context.SetStorage(storage_, *(context.GetStoragePattern()));
      context.StopMatch(true);
    } else if (singleton) {
      context.StopMatch(true, context.GetStoragePattern());
    } else {
      context.StopMatch(true);
    }
  } else {
    context.StopMatch(false);
  }
}

const std::wstring* PatternExpr::AsStr() const {
  if (nullptr != pattern_) {
    return pattern_->AsStr();
  } else if (nullptr != patternSet_) {
    return patternSet_->AsStr();
  }
  return nullptr;
}

void PatternExpr::DebugMatch_(Context &context, ssize_t startIdx, bool ok) {
  if (Conf::Get().GetDebugMode()) {
    DEBUG("pattern_expr["
        << GetRepr()
        << "] match["
        << context.GetSentence().GetSentence()
        << "] start["
        << startIdx
        << "] end["
        << context.GetCurPos()
        << "] res["
        << ok
        << "]");
  }
}

std::unordered_set<char> CreateInvalidLeadPosForWildcard() {
  std::unordered_set<char> result;
  result.insert('y');
  result.insert('w');
  return result;
}

std::unordered_set<std::string> CreateInvalidFullPosForWildcard() {
  std::unordered_set<std::string> result;
  result.insert("vshi");
  result.insert("vyou");
  result.insert("ry");
  return result;
}

}}}
