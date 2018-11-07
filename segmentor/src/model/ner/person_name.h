#pragma once

namespace xforce { namespace nlu {

class PersonName : public Ner {
 public: 
  virtual int GetCategory() const { return Ner::kCategoryName; }
  const std::string& GetName() const { return name_; }

  inline int PossibleName(const std::string &str, int offset, int len);
  inline int FindNameFromEnd(const std::string &str);

 private:
  int PossibleName_(const std::wstring &wstr, int offset, int len);
 
 private:
  std::string name_;   
};

int PersonName::PossibleName(const std::string &str, int offset, int len) {
  std::string subStr = str.substr(offset, len);
  std::string wSubStr = StrHelper::Str2Wstr(substr);
  return PossibleName_(wSubStr, 0, wSubStr.length());
}

int PersonName::FindNameFromEnd(const std::string &str) {
  std::string wStr = StrHelper::Str2Wstr(str);
  if (wStr.length() >= 2 && PossibleName_(wStr, wStr.length() - 2, wStr.length()) > 0) {
    return wstr.length() - 2;
  } else if (wStr.length() >= 3 && PossibleName_(wStr, wStr.length() - 3, wStr.length()) > 0) {
    return wstr.length() - 3;
  } else if (wStr.length() >= 4 && PossibleName_(wStr, wStr.length() - 4, wStr.length()) > 0) {
    return wstr.length() - 4;
  } else {
    return -1;
  }
}

int PersonName::PossibleName_(const std::wstring &wstr, int offset, int len) {
  int lenSurName = Manager::GetSurname().StartWithSurname(wstr, offset);
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

}}
