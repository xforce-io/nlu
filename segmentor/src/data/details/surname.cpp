#include "../surname.h"

namespace xforce { namespace nlu { namespace segmentor {

bool Surname::Init(const std::string &dictpath) {
  FILE *fp = fopen(dictpath.c_str(), "r");
  if (fp == nullptr) {
    ERROR("fail_open_filepath[" << *StrHelper::Str2Wstr(dictpath) << "]");
    return false;
  }

  char buf[4096];
  char *line = fgets(buf, sizeof(buf), fp);
  std::vector<std::string> results;
  while (nullptr!=line) {
    if (buf[strlen(buf) - 1] == '\n') {
      buf[strlen(buf) - 1] = '\0';
    }

    if (buf[strlen(buf) - 1] == '\r') {
      buf[strlen(buf) - 1] = '\0';
    }

    if (strlen(buf) > 0) {
      auto wstr = StrHelper::Str2Wstr(buf);
      if (nullptr == wstr) {
        ERROR("fail_parse_surname[" << buf << "]");
        return false;
      }
      container_.insert(std::make_pair((*wstr)[0], *wstr));
    }
    line = fgets(buf, sizeof(buf), fp);
  }
  fclose(fp);
  return true;
}

int Surname::StartWithSurname(const std::wstring &wstr, size_t offset) const {
  if (wstr.empty()) {
    return -1;
  }

  auto iter = container_.find(wstr[offset]);
  if (iter == container_.end()) {
    return -1;
  }

  if (iter->second.length() == 1) {
    return 1;
  } else if (wstr.substr(offset, 2).compare(iter->second) == 0) {
    return 2;
  }
  return -1;
}

}}}
