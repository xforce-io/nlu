#include "../struct_pattern_set.h"

namespace xforce { namespace nlu { namespace milkie {

std::shared_ptr<StructPatternSet> StructPatternSet::Parse(
    const std::wstring &blockKey,
    const std::wstring &statement) {
  if (statement.empty() || statement[0] != '[') {
    FATAL("invalid_pattern_set(" << blockKey << "|" << statement << "]");
    return NULL;
  }


}

std::shared_ptr<StructPatternSet> ParseForStrSet(
    const std::wstring &blockKey,
    const std::wstring &statement) {
  std::unordered_set<std::wstring> patternStrs;
  ssize_t curIdx = 1;
  bool reachEndMark = false;
  bool exit = false;
  while (!exit && curIdx < statement.length()) {
    if (' ' == statement[curIdx] ||
        ',' == statement[curIdx]) {
      ++curIdx;
    } else if (']' == statement[curIdx]) {
      reachEndMark = true;
      exit = true;
    } else if ('"' == statement[curIdx]) {
      ssize_t endIdx = statement.find('"', curIdx+1);
      if (endIdx>=0) {
        patternStrs.push_back(statement.substr(curIdx+1, endIdx-curIdx-1));
        curIdx = endIdx+1;
      } else {
        exit = true;
      }
    } else {
      exit = true;
    }
  }

  if (reachEndMark) {
    return new StructPatternSet(
        statement.substr(0, curIdx+1),
        patternStrs,
        NULL);
  } else {
    return NULL;
  }
}

std::shared_ptr<StructPatternSet> StructPatternSet::ParseForPatternExprSet(
    const std::wstring &blockKey,
    const std::wstring &statement) {
  std::vector<std::shared_ptr<PatternExpr>> patternExprs;
  ssize_t curIdx = 1;
  bool reachEndMark = false;
  bool exit = false;
  while (!exit && curIdx < statement.length()) {
    if (' ' == statement[curIdx] ||
        ',' == statement[curIdx]) {
      ++curIdx;
    } else if (']' == statement[curIdx]) {
      reachEndMark = true;
      exit = true;
    } else if ()
      //TODO
  }
}

}}}
