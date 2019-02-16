#include "../code_seg.h"
#include "../../context/context.h"

#include <lua/lua.hpp>

namespace xforce { namespace nlu { namespace milkie {

CodeSeg::CodeSeg(const std::wstring &code)
    :code_(code) {
  lock_ = new SpinLock();
  luaState_ = luaL_newstate();
  luaL_openlibs(luaState_);
}

CodeSeg::~CodeSeg() {
  lua_close(luaState_);
  XFC_DELETE(lock_)
}

int CodeSeg::Match(Context &context) {
  lock_->Lock();
  lua_newtable(luaState_);

  std::unordered_map<std::wstring, std::wstring> kvs;
  context.GetStorages(kvs);
  for (auto iter = kvs.begin(); iter != kvs.end(); ++iter) {
    lua_pushstring(luaState_, StrHelper::Wstr2Str(iter->first)->c_str());
    lua_pushstring(luaState_, StrHelper::Wstr2Str(iter->second)->c_str());
    lua_settable(luaState_, -3);
  }

  auto curPattern = StrHelper::Wstr2Str(*(context.GetCurPattern()));
  lua_pushstring(luaState_, "_p_");
  lua_pushstring(luaState_, curPattern->c_str());
  lua_settable(luaState_, -3);

  int num;
  if (StrHelper::GetNum(curPattern->c_str(), num)) {
    lua_pushstring(luaState_, "_pn_");
    lua_pushinteger(luaState_, num);
    lua_settable(luaState_, -3);
  }


  lua_setglobal(luaState_, "request");

  int ret = luaL_loadstring(luaState_, StrHelper::Wstr2Str(code_)->c_str());
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

std::shared_ptr<CodeSeg> CodeSeg::Build(const std::wstring &code) {
  if (code.at(0) != L'|' || code.at(code.length()-1) != L'|' || code.length() <= 2) {
    return nullptr;
  }
  return std::make_shared<CodeSeg>(code);
}

}}}
