#include "public.h"

namespace xforce { namespace nlu { namespace milkie {

class PatternExpr;  
class Refer;

class ReferManager {
 public: 
  bool PutLocalRefer(const std::wstring &blockKey, const std::wstring &line);
  std::shared_ptr<PatternExpr> Get(const std::wstring &blockKey, const std::wstring &key);

  static ReferManager& Get() { return referManager_; }

 private:  
  std::unordered_map<std::wstring, std::shared_ptr<Refer>> localDict_;

  static ReferManager referManager_;  
};

}}}
