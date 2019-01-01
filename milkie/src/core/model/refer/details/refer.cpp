#include "../refer.h"

namespace xforce { namespace nlu { namespace milkie {

void Refer::Put(
    const std::wstring &key, 
    std::shared_ptr<PatternExpr> &patternExpr) {
  patternExpr->SetStorageKey(key);
  theMap_.insert(std::make_pair(key, patternExpr));
}

bool Refer::Put(
    const std::wstring &key, 
    const std::wstring &line) {
  std::wstring trimed = StrHelper::Trim(line);
  if (trimed.empty()) {
    return true;
  }

  std::wstring lineAfterProcess = Helper::PreprocessExprLine(trimed);
  ssize_t idxEq = lineAfterProcess.find(L'=');
  if (idxEq<0 || idxEq == 0 || idxEq == lineAfterProcess.length() - 1) {
    FATAL("invalid_dict_line_pattern(" << lineAfterProcess << ")");
    return false;
  }

  std::wstring key = lineAfterProcess.substr(0, idxEq);
  std::wstring value = lineAfterProcess.substr(idxEq+1);
  if (!Variable::IsVariableName(key)) {
    FATAL("invalid_dict_variable_key(" << key << ")");
    return false;
  }

  auto ret = PatternExpr::Build(blockKey, value);
  if (ret.second != value.length()) {
    FATAL("invalid_dict_val(" << value << ")");
    return false;
  }
  Put(key, ret.first);
  return true;
}

void Refer::Clear() {
  theMap_.clear();
}

}}}
