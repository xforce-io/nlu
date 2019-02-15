#include "../word_dict.h"

#include "../dict_item.h"

namespace xforce { namespace nlu { namespace basic {

size_t WordDict::kMaxSizeDict = 100*1024*1024;

bool WordDict::Init(const std::string &filepath) {
  FILE *fp = fopen(filepath.c_str(), "r");
  if (fp == NULL) {
    ERROR("fail_open_filepath[" << filepath << "]");
    return false;
  }

  char *buf = new char [kMaxSizeDict];
  char *line = fgets(buf, kMaxSizeDict, fp);
  if (NULL == line) {
    FATAL("fail_read_word_dict_from[" << filepath << "]");
    return false;
  }

  const JsonType *jsonType = JsonType::ParseJson(buf);
  if (NULL == jsonType || !jsonType->IsDict()) {
    FATAL("fail_parse_word_dict_from[" << filepath << "]");
    return false;
  }

  for (auto &pair : jsonType->AsDict()) {
    if (!AddItem_(pair.first, pair.second)) {
      FATAL("fail_add_dict_item");
      return false;
    } 
  }

  fclose(fp);
  return true;
}

WordDict::~WordDict() {
  for (auto &pair : container_) {
    for (auto *dictItem : pair.second) {
      delete dictItem;
    }
  }
}

bool WordDict::AddItem_(const std::string &name, const JsonType &jsonType) {
  if (!jsonType.IsList()) {
    return false;
  }

  std::shared_ptr<std::wstring> nameWstr = StrHelper::Str2Wstr(name);
  if (nullptr == nameWstr) {
    FATAL("fail_convert_name_to_wstr[" << name << "]");
    return false;
  }

  std::vector<DictItem*> dictItems;
  for (size_t i=0; i < jsonType.AsList().size(); ++i) {
    DictItem *dictItem = DictItem::CreateFromJson(jsonType[i]);
    if (NULL == dictItem) {
      FATAL("fail_create_dict_item");
      return false;
    }
    dictItems.push_back(dictItem);
  }
  container_.insert(std::make_pair(*nameWstr, dictItems));
  return true;
}

}}}
