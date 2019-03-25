#include "../refer.h"
#include "../../variable/variable.h"
#include "../../pattern_expr/pattern_expr.h"

namespace xforce { namespace nlu { namespace milkie {

Refer::Refer(const ReferManager &referManager) :
  referManager_(referManager) {}

void Refer::Put(
    const std::wstring &key, 
    std::shared_ptr<PatternExpr> &patternExpr) {
  patternExpr->SetStorageKey(key);
  theMap_.insert(std::make_pair(key, patternExpr));
}

bool Refer::Put(
    const std::wstring &blockKey,
    const std::wstring &line) {
  std::wstring trimed = StrHelper::Trim(line);
  if (trimed.empty()) {
    return true;
  }

  std::wstring lineAfterProcess = Helper::PreprocessExprLine(trimed);
  ssize_t idxEq = lineAfterProcess.find(L'=');
  if (idxEq<0 || idxEq == 0 || idxEq == (ssize_t)(lineAfterProcess.length() - 1)) {
    FATAL("invalid_dict_line_pattern(" << lineAfterProcess << ")");
    return false;
  }

  std::wstring theKey = lineAfterProcess.substr(0, idxEq);
  std::wstring value = lineAfterProcess.substr(idxEq+1);
  if (!Variable::IsVariableName(blockKey)) {
    FATAL("invalid_dict_variable_key(" << blockKey << ")");
    return false;
  }

  auto ret = PatternExpr::Build(referManager_, blockKey, value);
  if (ret.second != value.length()) {
    FATAL("invalid_dict_val(" << value << ")");
    return false;
  }
  Put(theKey, ret.first);
  return true;
}

void Refer::Clear() {
  theMap_.clear();
}

}}}
