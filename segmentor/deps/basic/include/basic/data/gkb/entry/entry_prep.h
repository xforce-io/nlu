#pragma once

#include "../../../public.h"
#include "../../../model/pos/pos_tag.h"
#include "entry.h"

namespace xforce { namespace nlu { namespace basic {

class EntryPrep : public Entry {
 public:
  const static size_t kColTiWei = 1;
  const static size_t kColAfterWords = 2;
  const static size_t kColAfterPoses = 3;

  struct TiWei {
    enum Val {
      kNone,
      kTi,
      kWei,
      kJian,
      kOther,
    };
  };

 public:
  int Parse(const std::vector<std::wstring> &items);

  TiWei::Val TiWei() const { return tiWei_; }
  inline const std::vector<std::wstring>& GetAfterWords() const;
  inline const std::vector<PosTag::Type::Val>& GetAfterPoses() const;

 private:
  TiWei::Val tiWei_;
  std::vector<std::wstring> afterWords_;
  std::vector<PosTag::Type::Val> afterPoses_;
};

const std::vector<std::wstring>& EntryPrep::GetAfterWords() const {
  return afterWords_;
}

const std::vector<PosTag::Type::Val>& EntryPrep::GetAfterPoses() const {
  return afterPoses_;
}

}}}
