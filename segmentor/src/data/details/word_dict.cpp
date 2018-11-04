#include "../word_dict.h"

#include "../../model/core_dict_item.h"

namespace xforce { namespace nlu {

bool WordDict::Init(const std::vector<std::string> &filepaths) {
  simpleTrie_ = new xforce::SimpleTrie();
  for (auto iter = filepaths.begin(); iter != filepaths.end(); ++iter) {
    bool ret = Init_(*iter);
    if (!ret) {
      ERROR("fail_init_word_dict[" << *iter << "]");
      return false;
    }
  }
  return true;
}

void WordDict::PrefixMatch(
    const std::string &query, 
    std::vector<const CoreDictItem*> &coreDictItems) const {
  std::vector<size_t> prefixOffsets;
  simpleTrie_->PrefixesOf(query.c_str(), query.length(), prefixOffsets);
  for (auto iter = prefixOffsets.begin(); iter != prefixOffsets.end(); ++iter) {
    std::string tmpStr = std::string(query.c_str(), *iter);
    auto iter2 = container_.find(tmpStr);
    coreDictItems.push_back(iter2->second);
  }
}

const CoreDictItem* WordDict::GetCoreDictItem(const std::string &word) const {
    auto iter = container_.find(word);
    if (iter != container_.end()) {
      return iter->second;
    } else {
      return NULL;
    }
}

ssize_t WordDict::GetFreq(const std::string &word) const {
  const CoreDictItem *coreDictItem = GetCoreDictItem(word);
  if (coreDictItem != NULL) {
    return coreDictItem->GetFreq();
  } else {
    return -1;
  }
}

WordDict::~WordDict() {
  XFC_DELETE(simpleTrie_)
  for (auto iter = container_.begin(); iter != container_.end(); ++iter) {
    XFC_DELETE(iter->second)
  }  
}

bool WordDict::Init_(const std::string &filepath) {
  FILE *fp = fopen(filepath.c_str(), "r");
  if (fp == NULL) {
    ERROR("fail_open_filepath[" << filepath << "]");
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
      if (results.size() == 2) {
        CoreDictItem *coreDictItem = new CoreDictItem();
        bool ret = coreDictItem->Init(results);
        if (!ret) {
          ERROR("fail_init_core_dict_item[" << buf << "]");
          return false;
        }

        if (container_.find(coreDictItem->GetName()) == container_.end()) {
          container_.insert(std::make_pair(coreDictItem->GetName(), coreDictItem));
          simpleTrie_->Insert(coreDictItem->GetName().c_str(), coreDictItem->GetName().length());
        } else {
          XFC_DELETE(coreDictItem)
        }
      } else {
        ERROR("invalid_word_dict_format[" << buf << "]");
        return false;
      }
    }
    line = fgets(buf, sizeof(buf), fp);
  }
  fclose(fp);
  return true;
}

}}
