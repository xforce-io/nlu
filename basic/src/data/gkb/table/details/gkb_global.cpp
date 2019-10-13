#include "../gkb_global.h"
#include "../../../../data/gkb/gkb.h"

namespace xforce { namespace nlu { namespace basic {

std::shared_ptr<std::vector<PosTag::Type::Val>> GkbGlobal::GetPosTags(const std::wstring &word) const {
  const std::vector<const EntryGlobal*> *entries = GetEntries(word);
  if (nullptr == entries) {
    return nullptr;
  }

  auto result = std::make_shared<std::vector<PosTag::Type::Val>>();
  for (auto *entry : *entries) {
    result->push_back(entry->GetPosTag());
  }
  return result;
}

}}}
