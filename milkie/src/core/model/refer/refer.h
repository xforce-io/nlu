#include "../../../public.h"

namespace xforce { namespace nlu { namespace milkie {

class Conf;  
class ReferManager;
class PatternExpr;  

class Refer {
 public:
  explicit Refer(const Conf &conf, const ReferManager &referManager);

  const ReferManager& GetReferManager() const { return referManager_; }

  void Put(const std::wstring &key, std::shared_ptr<PatternExpr> &patternExpr);
  bool Put(const std::wstring &key, const std::wstring &line);
  inline const std::shared_ptr<PatternExpr> Get(const std::wstring &key) const;
  void Clear();

 private:
  const Conf &conf_;
  const ReferManager &referManager_;

  std::unordered_map<std::wstring, std::shared_ptr<PatternExpr>> theMap_; 
};

const std::shared_ptr<PatternExpr> Refer::Get(const std::wstring &key) const {
  auto iter = theMap_.find(key);
  if (iter != theMap_.end()) {
    return iter->second;
  } else {
    return nullptr;
  }
}

}}}
