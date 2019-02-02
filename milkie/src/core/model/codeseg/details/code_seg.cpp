#include "../code_seg.h"

#include <lua/lua.hpp>

namespace xforce { namespace nlu { namespace milkie {

CodeSeg::CodeSeg(const std::string &code)
    :code_(code) {
  lock_ = new SpinLock();
  luaState_ = luaL_newstate();
  luaL_openlibs(luaState_);
}

CodeSeg::~CodeSeg() {
  lua_close(luaState_);
  XFC_DELETE(lock_)
}

int CodeSeg::Match() {
  lock_->Lock();
  lua_newtable(luaState_);
  Request::const_iterator iter;
  for (iter = request.begin(); iter != request.end(); ++iter) {
    assert(iter->first != NULL);
    assert(iter->second != NULL);
    lua_pushstring(luaState_, iter->first);
    lua_pushstring(luaState_, iter->second);
    lua_settable(luaState_, -3);
  }
  lua_setglobal(luaState_, "request");

  int ret = luaL_loadstring(luaState_, code_.c_str());
  XFC_FAIL_HANDLE(LUA_OK!=ret)

  ret = lua_pcall(luaState_, 0, 0, 0);
  XFC_FAIL_HANDLE(LUA_OK!=ret)

  lua_getglobal(luaState_, "ret");
  ret = lua_toboolean(luaState_, -1);
  lua_pop(luaState_, 1);
  lock_->Unlock();
  return ret;

  ERROR_HANDLE:
  lua_pop(luaState_, 1);
  lock_->Unlock();
  return -1;
}

}}}