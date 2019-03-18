#pragma once

#include "../public.h"
#include "../model/pos/pos_tag.h"

namespace xforce { namespace nlu { namespace basic {

struct DictItem {
 public:
   inline static DictItem* CreateFromJson(const JsonType &jsonType);

 public: 
   PosTag::Type posTag; 
   std::string shape;
   std::string pinyin;
   NotionOrForm::Type notionOrForm;
   NominalOrPredicate::Type nominalOrPredicate;
   SingleOrCompound::Type singleOrCompound;
};

DictItem* DictItem::CreateFromJson(const JsonType &jsonType) {
  if (!jsonType.IsDict()) {
    return NULL;
  }

  DictItem *dictItem = new DictItem();
  dictItem->posTag = PosTag::GetPosTag(jsonType["pos"].AsStr());
  dictItem->shape = jsonType["shape"].AsStr();
  dictItem->pinyin = jsonType["pinyin"].AsStr();
  dictItem->notionOrForm = NotionOrForm::GetNotionOrForm(jsonType["notionOrForm"].AsStr());
  dictItem->nominalOrPredicate = NominalOrPredicate::GetNominalOrPredicate(jsonType["nominalOrPredicate"].AsStr());
  dictItem->singleOrCompound = SingleOrCompound::GetSingleOrCompound(jsonType["singleOrCompound"].AsStr());
  return dictItem;
}

}}}
