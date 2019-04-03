#pragma once

#include "../public.h"
#include "fragment/manager_fragment_set.h"

namespace xforce { namespace nlu { namespace basic {

class NluContext {
 public:
  inline explicit NluContext(const std::wstring &query); 

  const std::wstring& GetQuery() const { return query_; }

 private:
  std::wstring query_;
  ManagerFragmentSet managerFragmentSet_;
};

NluContext::NluContext(const std::wstring &query) :
  query_(query),
  segments_(query),
  chunks_(query) {}

void NluContext::SetSegments(const typename Segment::Set &segments) {
  segments_ = segments;
}

void NluContext::SetChunks(const typename Chunk::Set &chunks) {
  chunks_ = chunks;
}

}}}
