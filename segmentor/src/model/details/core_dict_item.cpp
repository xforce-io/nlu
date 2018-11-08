#include "../core_dict_item.h"
#include "../core_dict_natures.h"

namespace xforce { namespace nlu {

bool CoreDictItem::Init(const std::vector<std::string> &items) {
  if (items.size() <= 1) {
    return false;
  }

  StrHelper::Str2Wstr(items[0], name_);

  coreDictNatures_ = new CoreDictNatures();
  bool ret = coreDictNatures_->Init(items[1]);
  if (!ret) {
    WARN("fail_create_core_dict_natures_from[" << items[1] << "]");
    return false;
  }
  return true;
}

CoreDictItem::~CoreDictItem() {
  XFC_DELETE(coreDictNatures_)
}

}}
