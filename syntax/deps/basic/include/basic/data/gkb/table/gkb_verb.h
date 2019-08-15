#pragma once

#include "../../../public.h"
#include "../entry/entry_verb.h"
#include "table.hpp"
#include "gkb_verb_dongjie.h"
#include "gkb_verb_dongqu.h"

namespace xforce { namespace nlu { namespace basic {

class GkbVerb : public Table<EntryVerb> {
 private:
  typedef Table<EntryVerb> Super;

 public:
  virtual bool Init(
          const std::string &dir,
          const std::string &filepath);

  inline bool IsDongjie(const std::wstring &word);
  inline bool IsDongqu(const std::wstring &word);

  virtual bool IsDongjieOrDongquPhrase(
      const std::wstring &word0,
      const std::wstring &word1) const;

  EntryVerb::TiWeiZhun::Val TiWeiZhun(
          const std::wstring &word) const;

 private:
  std::unordered_set<std::wstring> dongjie_;
  std::unordered_set<std::wstring> dongqu_;

  GkbVerbDongjie *gkbVerbDongjie_;
  GkbVerbDongqu *gkbVerbDongqu_;
};

bool GkbVerb::IsDongjie(const std::wstring &word) {
  return dongjie_.find(word) != dongjie_.end();
}

bool GkbVerb::IsDongqu(const std::wstring &word) {
  return dongqu_.find(word) != dongqu_.end();
}

}}}
