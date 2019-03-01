#include "../word_dict.h"

#include "../../model/core_dict_item.h"

namespace xforce { namespace nlu { namespace segmentor {

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
    const std::wstring &query, 
    std::vector<const CoreDictItem*> &coreDictItems) const {
  std::string strQuery;
  XFC_ASSERT(StrHelper::Wstr2Str(query, strQuery));

  std::vector<size_t> prefixOffsets;
  simpleTrie_->PrefixesOf(strQuery.c_str(), strQuery.length(), prefixOffsets);
  for (auto iter = prefixOffsets.begin(); iter != prefixOffsets.end(); ++iter) {
    std::string tmpStr(strQuery.c_str(), *iter);
    std::wstring tmpWstr;
    XFC_ASSERT(StrHelper::Str2Wstr(tmpStr, tmpWstr));

    auto iter2 = container_.find(tmpWstr);
    coreDictItems.push_back(iter2->second);
  }
}

const CoreDictItem* WordDict::GetCoreDictItem(const std::wstring &word) const {
    auto iter = container_.find(word);
    if (iter != container_.end()) {
      return iter->second;
    } else {
      return nullptr;
    }
}

ssize_t WordDict::GetFreq(const std::wstring &word) const {
  const CoreDictItem *coreDictItem = GetCoreDictItem(word);
  if (coreDictItem != nullptr) {
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
  if (fp == nullptr) {
    ERROR("fail_open_filepath[" << filepath << "]");
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

          std::string strName;
          XFC_ASSERT(StrHelper::Wstr2Str(coreDictItem->GetName(), strName));
          simpleTrie_->Insert(strName.c_str(), strName.length());
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

}}}
