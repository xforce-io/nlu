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

  inline bool IsDongjie(const std::wstring &word) const;
  inline bool IsDongqu(const std::wstring &word) const;

  virtual bool IsDongjieOrDongquPhrase(
      const std::wstring &word0,
      const std::wstring &word1) const;

  bool IsZhu(const std::wstring &word) const;
  bool TiWeiZhun(
      const std::wstring &word,
      bool &isArgTi,
      bool &isArgWei,
      bool &isArgZhun) const;

  inline bool IsArgNone(const std::wstring &word) const;

 private:
  std::unordered_set<std::wstring> dongjie_;
  std::unordered_set<std::wstring> dongqu_;

  GkbVerbDongjie *gkbVerbDongjie_;
  GkbVerbDongqu *gkbVerbDongqu_;
};

bool GkbVerb::IsDongjie(const std::wstring &word) const {
  return dongjie_.find(word) != dongjie_.end();
}

bool GkbVerb::IsDongqu(const std::wstring &word) const {
  return dongqu_.find(word) != dongqu_.end();
}

bool GkbVerb::IsArgNone(const std::wstring &word) const {
  bool isArgTi, isArgWei, isArgZhun;
  bool ret = TiWeiZhun(word, isArgTi, isArgWei, isArgZhun);
  return ret && !(isArgTi || isArgWei || isArgZhun);
}

}}}
