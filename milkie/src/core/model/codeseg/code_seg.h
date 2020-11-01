#pragma once

#include "../../../public.h"

class lua_State;

namespace xforce { namespace nlu { namespace milkie {

class Conf;  
class Context;

class CodeSeg {
 public:
  CodeSeg();
  bool Init(const Conf &conf, const std::wstring &code);
  virtual ~CodeSeg();

  /*
   * @return :
   *      > 0 => fail to match
   *     == 0 => succ in matching
   *      < 0 => error happened
   */
  int Match(Context &context);

  static std::shared_ptr<CodeSeg> Build(
      const Conf &conf, 
      const std::wstring &code);
  inline static bool IsStartingChar(char c);

 private:
  mutable xforce::SpinLock *lock_;
  lua_State *luaState_;
  std::wstring code_;
};

bool CodeSeg::IsStartingChar(char c) {
  return '|' == c;
}

}}}
