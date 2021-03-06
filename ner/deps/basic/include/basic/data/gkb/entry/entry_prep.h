#pragma once

#include "../../../public.h"
#include "../../../model/pos/pos_tag.h"
#include "entry.h"

namespace xforce { namespace nlu { namespace basic {

class EntryPrep : public Entry {
 public:
  const static size_t kColTiWei = 11;
  const static size_t kColAfterWords = 25;
  const static size_t kColAfterPoses = 26;

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

  inline bool IsAfterWord(const std::wstring &word) const;
  inline bool IsAfterPos(PosTag::Type::Val posTag) const;

  TiWei::Val TiWei() const { return tiWei_; }
  inline const std::vector<std::wstring>& GetAfterWords() const;
  inline const std::vector<PosTag::Type::Val>& GetAfterPoses() const;

 private:
  TiWei::Val tiWei_;
  std::vector<std::wstring> afterWords_;
  std::vector<PosTag::Type::Val> afterPoses_;
};

bool EntryPrep::IsAfterWord(const std::wstring &word) const {
  for (auto &afterWord : afterWords_) {
    if (word == afterWord) {
      return true;
    }
  }
  return false;
}

bool EntryPrep::IsAfterPos(PosTag::Type::Val posTag) const {
  for (auto afterPos : afterPoses_) {
    if (posTag == afterPos) {
      return true;
    }
  }
  return false;
}

const std::vector<std::wstring>& EntryPrep::GetAfterWords() const {
  return afterWords_;
}

const std::vector<PosTag::Type::Val>& EntryPrep::GetAfterPoses() const {
  return afterPoses_;
}

}}}
