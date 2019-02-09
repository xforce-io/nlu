#include "../../../public.h"

namespace xforce { namespace nlu { namespace milkie {

class PatternExpr;  
class Refer;

class ReferManager {
 public:
  static const std::wstring kGlobal;

 public:
  ReferManager();
  virtual ~ReferManager();

  /*
   * @return :
   *        true  => succ
   *        false => has error
   */
  bool BuildGlobalDict();
  bool AddToGlobalDict(const std::string &filepath);
  bool PutLocalRefer(const std::wstring &blockKey, const std::wstring &line);
  std::shared_ptr<PatternExpr> Get(const std::wstring &blockKey, const std::wstring &key);

  static ReferManager& Get() { return referManager_; }

 private:
  Refer *globalDict_;
  std::unordered_map<std::wstring, std::shared_ptr<Refer>> localDict_;

  static ReferManager referManager_;  
};

}}}
