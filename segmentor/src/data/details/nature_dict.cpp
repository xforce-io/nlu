#include "../nature_dict.h"
#include "../../model/nature.h"

namespace xforce { namespace nlu {

bool NatureDict::Init(const std::string &dictpath) {
  FILE *fp = fopen(dictpath.c_str(), "r");
  if (fp == NULL) {
    ERROR("fail_open_filepath[" << dictpath << "]");
    return false;
  }

  char buf[4096];
  char *line = fgets(buf, sizeof(buf), fp);
  std::vector<std::string> results;
  uint32_t maxLen = 0;
  while (NULL!=line) {
    if (buf[strlen(buf) - 1] == '\n') {
      buf[strlen(buf) - 1] = '\0';
    }

    if (buf[strlen(buf) - 1] == '\r') {
      buf[strlen(buf) - 1] = '\0';
    }

    if (strlen(buf) > 0) {
      StrHelper::SplitStr(buf, '\t', results);
      if (results.size() != 4) {
        ERROR("invalid_nature_dict_line[" << buf << "]"); 
        return false;
      }

      uint32_t index;
      bool ret = StrHelper::GetNum(results[0].c_str(), index);
      if (!ret) {
        ERROR("invalid_nature_dict_line[" << buf << "]"); 
        return false;
      }

      uint32_t freq;
      ret = StrHelper::GetNum(results[3].c_str(), freq);
      if (!ret) {
        ERROR("invalid_nature_dict_line[" << buf << "]");
        return false;
      }
      container_.insert(std::make_pair(results[2], new Nature(results[2], index, freq)));

      if (index > maxLen) { 
        maxLen = index;
      }
    }
    line = fgets(buf, sizeof(buf), fp);
  }
  indexSize_ = maxLen + 1;
  fclose(fp);
  return true;
}

NatureDict::~NatureDict() {
  for (auto iter = container_.begin(); iter != container_.end(); ++iter) {
    XFC_DELETE(iter->second)
  }
}

}}
