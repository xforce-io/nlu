#include "../../../public.h"

namespace xforce { namespace nlu { namespace milkie {

class Conf;
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
  bool BuildGlobalDict(const Conf &conf);
  bool AddToGlobalDict(const std::string &filepath);
  bool PutLocalRefer(const std::wstring &blockKey, const std::wstring &line);
  const std::shared_ptr<PatternExpr> Get(const std::wstring &blockKey, const std::wstring &key) const;

 private:
  Refer *globalDict_;
  std::unordered_map<std::wstring, std::shared_ptr<Refer>> localDict_;
};

}}}
