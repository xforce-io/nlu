#include <memory>
#include "../struct_pattern_set.h"
#include "../struct_pattern_set.h"
#include "../../../pattern_expr/pattern_expr.h"
#include "../../../refer/refer_manager.h"

namespace xforce { namespace nlu { namespace milkie {

std::shared_ptr<StructPatternSet> StructPatternSet::Parse(
    const ReferManager &referManager,
    const std::wstring &blockKey,
    const std::wstring &statement) {
  if (statement.empty() || statement[0] != '[') {
    FATAL("invalid_pattern_set(" << blockKey << "|" << statement << "]");
    return nullptr;
  }

  auto structPatternSet = ParseForStrSet(blockKey, statement);
  if (nullptr != structPatternSet) {
    return structPatternSet;
  } else {
    return ParseForPatternExprSet(referManager, blockKey, statement);
  }
}

std::shared_ptr<StructPatternSet> StructPatternSet::ParseForStrSet(
    const std::wstring &blockKey,
    const std::wstring &statement) {
  UNUSE(blockKey)

  std::unordered_set<std::wstring> patternStrs;
  ssize_t curIdx = 1;
  bool reachEndMark = false;
  bool exit = false;
  while (!exit && curIdx < (ssize_t)statement.length()) {
    if (' ' == statement[curIdx] ||
        ',' == statement[curIdx]) {
      ++curIdx;
    } else if (']' == statement[curIdx]) {
      reachEndMark = true;
      exit = true;
    } else if ('"' == statement[curIdx]) {
      ssize_t endIdx = statement.find('"', curIdx+1);
      if (endIdx>=0) {
        patternStrs.insert(statement.substr(curIdx+1, endIdx-curIdx-1));
        curIdx = endIdx+1;
      } else {
        exit = true;
      }
    } else {
      exit = true;
    }
  }

  if (reachEndMark) {
    return std::make_shared<StructPatternSet>(
        statement.substr(0, curIdx+1),
        &patternStrs,
        nullptr);
  } else {
    return nullptr;
  }
}

std::shared_ptr<StructPatternSet> StructPatternSet::ParseForPatternExprSet(
    const ReferManager &referManager,
    const std::wstring &blockKey,
    const std::wstring &statement) {
  std::vector<std::shared_ptr<PatternExpr>> patternExprs;
  ssize_t curIdx = 1;
  bool reachEndMark = false;
  bool exit = false;
  while (!exit && curIdx < (ssize_t)statement.length()) {
    if (' ' == statement[curIdx] ||
        ',' == statement[curIdx]) {
      ++curIdx;
    } else if (']' == statement[curIdx]) {
      reachEndMark = true;
      exit = true;
    } else if (PatternExpr::IsPatternExprStartingChar(statement[curIdx])) {
      auto ret = PatternExpr::Build(referManager, blockKey, statement.substr(curIdx));
      patternExprs.push_back(ret.first);
      curIdx += ret.second;
    } else {
      exit = true;
    }
  }

  if (reachEndMark) {
    return std::make_shared<StructPatternSet>(
            statement.substr(0, curIdx+1),
            nullptr,
            &patternExprs);
  } else {
    FATAL("invalid_pattern_set(" << blockKey << "|" << statement << ")");
    return nullptr;
  }
}

}}}
