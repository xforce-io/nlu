#pragma once

#include "../../../public.h"
#include "../entry/entry_verb.h"
#include "table.hpp"
#include "gkb_verb_dongqu.h"

namespace xforce { namespace nlu { namespace basic {

class GkbVerb : public Table<EntryVerb> {
 private:
  typedef Table<EntryVerb> Super;

 public:
  virtual bool Init(
          const std::string &dir,
          const std::string &filepath);

  virtual bool IsPhrase(
      const std::wstring &word0,
      const std::wstring &word1) const;

  EntryVerb::TiWeiZhun::Val TiWeiZhun(
          const std::wstring &word) const;

 private:
  GkbVerbDongqu *gkbVerbDongqu_;
};

}}}
