#pragma once

#include "public.h"
#include "name_entity.h"

namespace xforce { namespace nlu { namespace ner {

class PersonName : public NameEntity {
 private:
  typedef std::tr1::unordered_set<wchar_t> WcharSet;

 public: 
  explicit PersonName(const std::wstring &name, size_t offset); 

  virtual int GetCategory() const { return NameEntity::kCategoryName; }
  const std::wstring& GetName() const { return name_; }

  inline static int PossibleName(const std::wstring &wstr, int offset, int len);
  inline static int FindNameFromEnd(const std::wstring &wstr);

 private: 
  static WcharSet CreateForbiddenChars_();

 private:
  std::wstring name_;

  static WcharSet forbiddenChars_; 
};

}}}

#include "data/surname.h"
#include "data/manager.h"

namespace xforce { namespace nlu { namespace ner {

int PersonName::PossibleName(const std::wstring &wstr, int offset, int len) {
  int lenSurName = Manager::Get().GetSurname().StartWithSurname(wstr, offset);
  if (lenSurName < 0) {
    return -1;
  }

  for (size_t i=offset; i < (size_t)(offset+len); ++i) {
    if (forbiddenChars_.find(wstr.at(i)) != forbiddenChars_.end()) {
      return -1;
    }
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

}}}
