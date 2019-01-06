#include "../struct_pattern_expr.h"
#include "../../../pattern/pattern.h"
#include "../../../pattern_set/pattern_set.h"
#include "../../../pattern_expr/pattern_expr.h"
#include "../../../variable/variable.h"
#include "../../../refer/refer_manager.h"

namespace xforce { namespace nlu { namespace milkie {

StructPatternExpr::~StructPatternExpr() {
  XFC_DELETE(storage_)
  XFC_DELETE(patternExprs_)
}

std::shared_ptr<StructPatternExpr> StructPatternExpr::Parse(
    const std::wstring &blockKey, 
    const std::wstring &statement) {
  wchar_t startingChar = statement[0];
  if (Pattern::IsStartingChar(startingChar)) {
    auto ret = Pattern::Build(statement);
    return std::make_shared<StructPatternExpr>(statement.substr(0, ret.second), ret.first);
  } else if (PatternSet::IsStartingChar(startingChar)) {
    auto ret = PatternSet::Build(blockKey, statement);
    return std::make_shared<StructPatternExpr>(statement.substr(0, ret.second), ret.first);
  } else if (PatternExpr::IsExactStartingChar(startingChar)) {
    PatternExpr::Vector items;
    std::wstring storage;
    CategoryPatternExpr::Category categoryPatternExpr;

    ssize_t curIdx = 1;
    while (curIdx < statement.length()) {
      wchar_t curChar = statement[curIdx];
      if (L' ' == curChar) {
        ++curIdx;
      } else if (Pattern::IsStartingChar(curChar)) {
        auto ret = Pattern::Build(statement.substr(curIdx));
        items.push_back(std::make_shared<PatternExpr>(ret.first));
        curIdx += ret.second;
      } else if (PatternSet::IsStartingChar(curChar)) {
        auto ret = PatternSet::Build(blockKey, statement.substr(curIdx));
        items.push_back(std::make_shared<PatternExpr>(ret.first));
        curIdx += ret.second;
      } else if (PatternExpr::IsExactStartingChar(curChar)) {
        auto ret = PatternExpr::Build(blockKey, statement.substr(curIdx));
        items.push_back(ret.first);
        curIdx += ret.second;
      } else if (Variable::IsStartingChar(curChar)) {
        std::shared_ptr<std::wstring> variableName = Variable::GetVariableName(statement, curIdx+1);
        if (statement[curIdx+1] != L'*') {
          auto patternExpr = ReferManager::Get().Get(blockKey, *variableName);
          if (patternExpr.get() != nullptr) {
            FATAL("unknown_dict_key_in_expr(" << variableName << ")");
            return nullptr;
          }
          patternExpr->SetStorageKey(*variableName);
          items.push_back(patternExpr);
        } else {
          items.push_back(std::make_shared<PatternExpr>(variableName->substr(1)));
        }
        curIdx += variableName->length() + 1;
      } else if (curIdx+1 < statement.length() &&
          L'-' == curChar &&
          L'>' == statement[curIdx+1]) {
        curIdx += 2;
        while (curIdx < statement.length() &&
            L' ' == statement[curIdx]) {
          ++curIdx;
        }

        if (curIdx == statement.length()) {
          FATAL("invalid_storage(" << statement << ")");
          return nullptr;
        }

        storage = *(Variable::GetVariableName(statement, curIdx));
        curIdx += storage.length();
      } else if (L'*' == curChar) {
        categoryPatternExpr = CategoryPatternExpr::kZeroOrMore;
      } else if (L'+' == curChar) {
        categoryPatternExpr = CategoryPatternExpr::kOnceOrMore;
      } else if (L'?' == curChar) {
        categoryPatternExpr = CategoryPatternExpr::kZeroOrOnce;
      } else if (L'}' == curChar) {
        if (items.empty()) {
          FATAL("invalid_pattern_expr(" << statement << ")");
          return nullptr;
        }
        return std::make_shared<StructPatternExpr>(
            statement.substr(0, curIdx+1),
            nullptr,
            nullptr,
            nullptr,
            &items,
            &storage,
            categoryPatternExpr);
      } else {
        FATAL("invalid_pattern_expr(" << statement << ")");
        return nullptr;
      }
    }
  } else if (Variable::IsStartingChar(startingChar)) {
    auto variableName = Variable::GetVariableName(statement, 1);
    auto patternExpr = ReferManager::Get().Get(blockKey, *variableName);
    if (patternExpr.get() == nullptr) {
      FATAL("unknown_dict_key(" << variableName << ")");
      return nullptr;
    }

    patternExpr->SetStorageKey(*variableName);
    return std::make_shared<StructPatternExpr>(
        statement.substr(0, variableName->length() + 1),
        patternExpr);
  }
  FATAL("invalid_pattern_expr_starting_char(" << statement << ")");
  return nullptr;
}

}}}
