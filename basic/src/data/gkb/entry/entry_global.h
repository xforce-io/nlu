#pragma once

#include "../../../public.h"
#include "entry.h"
#include "../../../model/pos/pos_tag.h"

namespace xforce { namespace nlu { namespace basic {

class EntryGlobal : public Entry {
 public:
  int Parse(const std::vector<std::wstring> &items);

  PosTag::Type GetPosTag() const { return posTag_; }

 private:
  PosTag::Type posTag_; 
  std::wstring tongxing_;
  std::wstring pinyin_;
  std::wstring xushi_;
  std::wstring tiwei_;
  std::wstring danhe_;
};

}}}
