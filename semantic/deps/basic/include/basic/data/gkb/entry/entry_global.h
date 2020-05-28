#pragma once

#include "../../../public.h"
#include "entry.h"
#include "../../../model/pos/pos_tag.h"

namespace xforce { namespace nlu { namespace basic {

class EntryGlobal : public Entry {
 public:
  const static size_t kColPos = 1;
  const static size_t kColTiWei = 5;

  struct TiWei {
      enum Val {
          kNone,
          kTi,
          kWei,
      };
  };

 public:
  int Parse(const std::vector<std::wstring> &items);

  PosTag::Type::Val GetPosTag() const { return posTag_; }
  TiWei::Val GetTiWei() const { return tiWei_; }

 private:
  PosTag::Type::Val posTag_;
  TiWei::Val tiWei_;
};

}}}
