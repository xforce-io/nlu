#include "../core_dict_item.h"
#include "../core_dict_natures.h"
#include "../core_dict_nature.h"
#include "../nature.h"

namespace xforce { namespace nlu { namespace segmentor {

bool CoreDictItem::Init(const std::vector<std::string> &items) {
  if (items.size() <= 1) {
    return false;
  }

  auto tmp = StrHelper::Str2Wstr(items[0]);
  if (tmp == nullptr) {
    return false;
  }

  name_ = *tmp;

  coreDictNatures_ = new CoreDictNatures();
  bool ret = coreDictNatures_->Init(items[1]);
  if (!ret) {
    WARN("fail_create_core_dict_natures_from[" << *StrHelper::Str2Wstr(items[1]) << "]");
    return false;
  }
  return true;
}

basic::PosTag::Type::Val CoreDictItem::GetPosTag() const {
  const CoreDictNature *mainNature = coreDictNatures_->GetMainNature();
  return nullptr != mainNature ?
         mainNature->GetNature().GetPosTag() :
         basic::PosTag::Type::kUndef;
}

CoreDictItem::~CoreDictItem() {
  XFC_DELETE(coreDictNatures_)
}

}}}
