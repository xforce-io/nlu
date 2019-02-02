#pragma once

#include "../../../public.h"

class lua_State;

namespace xforce { namespace nlu { namespace milkie {

class CodeSeg {
 public:
  explicit CodeSeg(const std::string &code);
  virtual ~CodeSeg();

  /*
   * @return :
   *      > 0 => fail to match
   *     == 0 => succ in matching
   *      < 0 => error happened
   */
  int Match();

 private:
  mutable xforce::SpinLock *lock_;
  lua_State *luaState_;
  std::string code_;
};

}}}
