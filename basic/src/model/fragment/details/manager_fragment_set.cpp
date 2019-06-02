#include "../manager_fragment_set.h"

namespace xforce { namespace nlu { namespace basic {

ManagerFragmentSet::ManagerFragmentSet(const std::wstring &query) :
    nameEntities_(query),
    segments_(query),
    chunkSeps_(query),
    chunks_(query) {}

void ManagerFragmentSet::Dump(JsonType &jsonType) {
  nameEntities_.Dump(jsonType["nameEntities"]);
  segments_.Dump(jsonType["seg"]);
  chunkSeps_.Dump(jsonType["chunkSep"]);
  chunks_.Dump(jsonType["chunk"]);
}


}}}
