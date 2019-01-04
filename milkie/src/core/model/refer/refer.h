#include "../../../public.h"

namespace xforce { namespace nlu { namespace milkie {

class PatternExpr;  

class Refer {
 public:
  void Put(const std::wstring &key, std::shared_ptr<PatternExpr> &patternExpr);
  bool Put(const std::wstring &key, const std::wstring &line);
  inline std::shared_ptr<PatternExpr> Get(const std::wstring &key);
  void Clear();

 private: 
   std::unordered_map<std::wstring, std::shared_ptr<PatternExpr>> theMap_; 
};

std::shared_ptr<PatternExpr> Refer::Get(const std::wstring &key) {
  auto iter = theMap_.find(key);
  if (iter != theMap_.end()) {
    return iter->second;
  } else {
    return nullptr;
  }
}

}}}
