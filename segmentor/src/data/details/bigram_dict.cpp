#include "../bigram_dict.h"

namespace xforce { namespace nlu {

bool BigramDict::Init(const std::string &dictpath) {
  FILE *fp = fopen(dictpath.c_str(), "r");
  if (fp == NULL) {
    ERROR("fail_open_filepath[" << dictpath << "]");
    return false;
  }

  char buf[4096];
  char *line = fgets(buf, sizeof(buf), fp);
  std::vector<std::string> results;
  while (NULL!=line) {
    if (buf[strlen(buf) - 1] == '\n') {
      buf[strlen(buf) - 1] = '\0';
    }

    if (buf[strlen(buf) - 1] == '\r') {
      buf[strlen(buf) - 1] = '\0';
    }

    if (strlen(buf) > 0) {
      StrHelper::SplitStr(buf, '\t', results);
      if (results.size() != 2) {
        ERROR("invalid_bigram_dict_line[" << buf << "]"); 
        return false;
      }

      std::vector<std::string> results1;
      StrHelper::SplitStr(results[0], '@', results1);
      if (results1.size() != 2) {
        ERROR("invalid_bigram_dict_line[" << buf << "]"); 
        return false;
      }

      uint32_t num;
      bool ret = StrHelper::GetNum(results[1].c_str(), num);
      if (!ret) {
        ERROR("invalid_bigram_dict_line[" << buf << "]"); 
        return false;
      }

      std::wstring wstrWord0;
      std::wstring wstrWord1;
      XFC_ASSERT(StrHelper::Str2Wstr(results1[0], wstrWord0));
      XFC_ASSERT(StrHelper::Str2Wstr(results1[1], wstrWord1));
      AddToDict(wstrWord0, wstrWord1, num);  
    }
    line = fgets(buf, sizeof(buf), fp);
  }
  fclose(fp);
  return true;
}

uint32_t BigramDict::GetFreq(const std::wstring &word0, const std::wstring &word1) const {
  auto iter = container_.find(word0);
  if (iter == container_.end()) {
    return 0;
  }

  auto iter1 = iter->second->find(word1);
  if (iter1 == iter->second->end()) {
    return 0;
  }
  return iter1->second;
}

void BigramDict::AddToDict(const std::wstring &word0, const std::wstring &word1, uint32_t freq) {
  auto iter = container_.find(word0);
  if (iter == container_.end()) {
    Inner *inner = new Inner;
    inner->insert(std::make_pair(word1, freq));
    container_.insert(std::make_pair(word0, inner));
    return;
  }

  auto iter1 = iter->second->find(word1);
  if (iter1 == iter->second->end()) {
    iter->second->insert(std::make_pair(word1, freq));
    return;
  }

  iter->second->insert(std::make_pair(word1, iter1->second + freq));
}

BigramDict::~BigramDict() {
  for (auto iter = container_.begin(); iter != container_.end(); ++iter) {
    XFC_DELETE(iter->second)
  }
}

}}
