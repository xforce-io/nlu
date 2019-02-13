#include "../pattern_expr.h"
#include "../parser/struct_pattern_expr.h"
#include "../../pattern/pattern.h"
#include "../../pattern_set/pattern_set.h"
#include "../../../../conf/conf.h"
#include "../../variable/variable.h"
#include "../../codeseg/code_seg.h"

namespace xforce { namespace nlu { namespace milkie {

std::unordered_set<wchar_t> PatternExpr::invalidLeadPosForWildcard_ = PatternExpr::CreateInvalidLeadPosForWildcard();
std::unordered_set<std::wstring> PatternExpr::invalidFullPosForWildcard_ = PatternExpr::CreateInvalidFullPosForWildcard();

PatternExpr::PatternExpr(
    std::shared_ptr<Pattern> pattern,
    std::shared_ptr<PatternSet> patternSet,
    const std::wstring *wildcardName,
    std::shared_ptr<StructPatternExpr> structPatternExpr) :
    father_(nullptr),
    wildcardName_(nullptr),
    storageKey_(nullptr) {
  pattern_ = pattern;
  patternSet_ = patternSet;
  if (nullptr != wildcardName) {
    wildcardName_ = new std::wstring(*wildcardName);
  }
  structPatternExpr_ = structPatternExpr;

  if (nullptr != pattern ||
      nullptr != patternSet ||
      nullptr != wildcardName) {
    if (nullptr != patternSet) {
      patternSet_->SetFather(*this);
    }
    return;
  }

  if (structPatternExpr->GetPattern() != nullptr) {
    pattern_ = structPatternExpr_->GetPattern();
    return;
  } else if (structPatternExpr->GetPatternSet() != nullptr) {
    patternSet_ = structPatternExpr_->GetPatternSet();
    patternSet_->SetFather(*this);
    return;
  }

  if (structPatternExpr->GetItems() != nullptr) {
    items_ = *(structPatternExpr_->GetItems());
    for (auto &item : items_) {
      item->SetFather(*this);
    }
  }

  if (structPatternExpr->GetFilter() != nullptr) {
    filter_ = structPatternExpr_->GetFilter();
  }

  if (nullptr != structPatternExpr_) {
    if (structPatternExpr_->GetStorageKey() != nullptr) {
      SetStorageKey(*(structPatternExpr_->GetStorageKey()));
    }
    repeatPattern_ = structPatternExpr_->GetCategoryPatternExpr();
  }
}

PatternExpr::~PatternExpr() {
  XFC_DELETE(wildcardName_)
}

void PatternExpr::SetFather(const PatternExpr &patternExpr) {
  father_ = &patternExpr;
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

  if (nullptr != filter_ && filter_->Match(context) > 0) {
    context.StopMatch(false);
    DebugMatch_(context, startIdx, false);
    return false;
  }

  StopMatch(true, context, singleton);
  DebugMatch_(context, startIdx, true);
  return true;
}

ssize_t PatternExpr::MatchFromIdx(ssize_t fromIdx, Context &context) {
  ssize_t idx = fromIdx;
  while (idx < items_.size()) {
    auto patternExpr = items_[idx];
    if (nullptr != patternExpr->AsWildcard()) {
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
    StorageKey storageKeyForWildcard = StorageKey(
            storageKey_ != nullptr ? storageKey_->GetSpace() : nullptr,
            items_[itemIdx-1]->AsWildcard());

    context.StartMatch(offset);
    ssize_t retInner = MatchFromIdx(itemIdx, context);
    if (0 == retInner &&
        oldCurPos != offset &&
        context.GetCurPos() == context.GetSentence().GetSentence().length()) {
      context.SetStorageStr(
              storageKeyForWildcard,
              context.GetSentence().GetSentence().substr(oldCurPos, offset-oldCurPos));
      if (nullptr == filter_ || filter_->Match(context)) {
        context.StopMatch(true);
        if (nullptr != storageKey_) {
          context.SetStorage(*storageKey_, *(context.GetStoragePattern()));
        }
        return true;
      } else {
        context.RemoveStorage(storageKeyForWildcard);
      }
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
    if (nullptr != storageKey_) {
      context.SetStorage(*storageKey_, *(context.GetStoragePattern()));
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

bool PatternExpr::IsExactStartingChar(char c) {
  return '{' == c;
}

bool PatternExpr::IsPatternExprStartingChar(char c) {
  return IsPatternExprExactStartingChar(c) ||
    IsPatternExprPrefixStartingChar(c);
}

bool PatternExpr::IsPatternExprExactStartingChar(char c) {
  return Pattern::IsStartingChar(c) ||
    PatternSet::IsStartingChar(c) ||
    PatternExpr::IsExactStartingChar(c) ||
    Variable::IsStartingChar(c);
}

bool PatternExpr::IsPatternExprPrefixStartingChar(char c) {
  return '^' == c;
}

std::pair<std::shared_ptr<PatternExpr>, ssize_t> PatternExpr::Build(
        const std::wstring &blockKey,
        const std::wstring &statement) {
  auto structPatternExpr = StructPatternExpr::Parse(blockKey, statement);
  if (nullptr == structPatternExpr) {
    return std::make_pair(nullptr, -1);
  }

  if (nullptr == structPatternExpr->GetPatternExpr()) {
    return std::make_pair(
            std::make_shared<PatternExpr>(structPatternExpr),
            structPatternExpr->GetStatement().length());
  } else {
    return std::make_pair(
            structPatternExpr->GetPatternExpr(),
            structPatternExpr->GetStatement().length());
  }
}

std::shared_ptr<PatternExpr> PatternExpr::Build(std::shared_ptr<Pattern> &pattern) {
  return std::make_shared<PatternExpr>(pattern);
}

std::shared_ptr<PatternExpr> PatternExpr::Build(std::shared_ptr<PatternSet> &patternSet) {
  return std::make_shared<PatternExpr>(patternSet);
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

std::unordered_set<wchar_t> PatternExpr::CreateInvalidLeadPosForWildcard() {
  std::unordered_set<wchar_t> result;
  result.insert(L'y');
  result.insert(L'w');
  return result;
}

std::unordered_set<std::wstring> PatternExpr::CreateInvalidFullPosForWildcard() {
  std::unordered_set<std::wstring> result;
  result.insert(L"vshi");
  result.insert(L"vyou");
  result.insert(L"ry");
  return result;
}

}}}
