#include "../struct_pattern_expr.h"

namespace xforce { namespace nlu { namespace milkie {

std::shared_ptr<StructPatternExpr> StructPatternExpr::Parse(
    const std::wstring &blockKey, 
    const std::wstring &statement) {
  wchar_t startingChar = statement[0];
  if (Pattern::IsStartingChar(startingChar)) {
    auto ret = Pattern::Build(statement);
    return std::make_shared<StructPatternExpr>(statement.substr(0, ret.second), ret.first.get());
  } else if (PatternSet::IsStartingChar(startingChar)) {
    auto ret = PatternSet::Build(blockKey, statement);
    return std::make_shared<StructPatternExpr>(statement.substr(0, ret.second), ret.first.get());
  } else if (PatternExpr::IsExactStartingChar(startingChar)) {
    PatternExprs items;
    std::wstring storage;
    PatternExpr::Category categoryPatternExpr;

    ssize_t curIdx = 1;
    while (curIdx < statement.length()) {
      wchar_t curChar = statement[curIdx];
      if (L' ' == curChar) {
        ++curIdx;
      } else if (Pattern::IsStartingChar(curChar)) {
        auto ret = Pattern::Build(statement.substr(curIdx));
        items.push_back(std::make_pair<PatternExpr>(*(ret.first));
        curIdx += ret.second;
      } else if (PatternSet::IsStartingChar(curChar)) {
        auto ret = PatternSet::Build(blockKey, statement.substr(curIdx));
        items.push_back(std::make_pair<PatternExpr>(*(ret.first))));
        curIdx += ret.second;
      } else if (PatternExpr::IsStartingChar(curChar)) {
        auto ret = PatternExpr::Build(blockKey, statement.substr(curIdx));
        items.push_back(std::make_pair<PatternExpr>(*(ret.first))));
        curIdx += ret.second;
      } else if ()
    }
  }
}

}}}
