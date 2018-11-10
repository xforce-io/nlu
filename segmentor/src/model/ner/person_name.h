#pragma once

#include "public.h"
#include "ner.h"

namespace xforce { namespace nlu {

class PersonName : public Ner {
 public: 
  explicit PersonName(const std::wstring &name); 

  virtual int GetCategory() const { return Ner::kCategoryName; }
  const std::wstring& GetName() const { return name_; }

  inline static int PossibleName(const std::wstring &wstr, int offset, int len);
  inline static int FindNameFromEnd(const std::wstring &wstr);

 private:
  std::wstring name_;
};

}}

#include "../../data/manager.h"
#include "../../data/surname.h"

namespace xforce { namespace nlu {

int PersonName::PossibleName(const std::wstring &wstr, int offset, int len) {
  int lenSurName = Manager::Get().GetSurname().StartWithSurname(wstr, offset);
  if (lenSurName < 0) {
    return -1;
  }

  if ((1 == lenSurName && (2 == len || 3 == len)) ||
      (2 == lenSurName && (3 == len || 4 == len))) {
    return lenSurName;
  } else {
    return -1;
  }
}

int PersonName::FindNameFromEnd(const std::wstring &wstr) {
  if (wstr.length() >= 2 && PossibleName(wstr, wstr.length() - 2, wstr.length()) > 0) {
    return wstr.length() - 2;
  } else if (wstr.length() >= 3 && PossibleName(wstr, wstr.length() - 3, wstr.length()) > 0) {
    return wstr.length() - 3;
  } else if (wstr.length() >= 4 && PossibleName(wstr, wstr.length() - 4, wstr.length()) > 0) {
    return wstr.length() - 4;
  } else {
    return -1;
  }
}

}}
