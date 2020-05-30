#pragma once

#include "../../public.h"
#include "kg_adapter.h"

namespace xforce { namespace nlu { namespace basic {

class KgAdapterMgr {
 public:
  inline static void Set(std::shared_ptr<KgAdapter> kgAdapter);
  inline static std::shared_ptr<KgAdapter> Get();

 private:
  static std::shared_ptr<KgAdapter> adapter_;
};

void KgAdapterMgr::Set(std::shared_ptr<KgAdapter> adapter) {
  adapter_ = adapter;
}

std::shared_ptr<KgAdapter> KgAdapterMgr::Get() {
  return adapter_;
}

}}}