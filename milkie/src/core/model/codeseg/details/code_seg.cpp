#include "../code_seg.h"
#include "../../context/context.h"
#include "../../../../conf/conf.h"

#include <lua/lua.hpp>

namespace xforce { namespace nlu { namespace milkie {

CodeSeg::CodeSeg() :
  lock_(nullptr),
  luaState_(nullptr) {}

bool CodeSeg::Init(const Conf &conf, const std::wstring &code) {
  if (code.find(L"ret =") == std::wstring::npos && code.find(L"ret=") == std::wstring::npos) {
    code_ = std::wstring(L"ret = ") + code;
  } else {
    code_ = code;
  }

  lock_ = new SpinLock();
  luaState_ = luaL_newstate();
  luaL_openlibs(luaState_);
  for (auto &luaPath : conf.GetCodeSegFilepaths()) {
    int ret = luaL_loadfile(luaState_, luaPath.c_str());  
    if(ret) {  
      FATAL("fail_load_lua[" << luaPath.c_str() << "]");
      return false;  
    }  
  }
  return true;
}

CodeSeg::~CodeSeg() {
  if (nullptr != luaState_) {
    lua_close(luaState_);
  }
  XFC_DELETE(lock_)
}

int CodeSeg::Match(Context &context) {
  lock_->Lock();
  lua_newtable(luaState_);

  const Storage& storage = context.GetStorage();
  for (auto iter = storage.Get().begin(); iter != storage.Get().end(); ++iter) {
    std::wstring tmpStr;
    iter->first.GetRepr(tmpStr);
    lua_pushstring(luaState_, StrHelper::Wstr2Str(tmpStr)->c_str());
    lua_pushstring(luaState_, StrHelper::Wstr2Str(*(iter->second->GetAsString()))->c_str());
    lua_settable(luaState_, -3);
  }
  lua_setglobal(luaState_, "r");

  auto curPatternWstr = *(context.GetCurPattern()->GetAsString());
  auto curPattern = StrHelper::Wstr2Str(curPatternWstr);
  lua_pushstring(luaState_, curPattern->c_str());
  lua_setglobal(luaState_, "_p_");

  if (code_.find(L"_pn_") != std::wstring::npos) {
    int num;
    if (StrHelper::GetNum(curPattern->c_str(), num)) {
      lua_pushinteger(luaState_, num);
      lua_setglobal(luaState_, "_pn_");
    }
}

  if (code_.find(L"_pl_") != std::wstring::npos) {
    lua_pushinteger(luaState_, curPatternWstr.length());
    lua_setglobal(luaState_, "_pl_");
  }

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

std::shared_ptr<CodeSeg> CodeSeg::Build(
    const Conf &conf,
    const std::wstring &code) {
  if (code.at(0) != L'|' || code.at(code.length()-1) != L'|' || code.length() <= 2) {
    return nullptr;
  }
  auto codeSeg = std::make_shared<CodeSeg>();
  return codeSeg->Init(conf, code.substr(1, code.length()-2)) ? codeSeg : nullptr;
}

}}}
