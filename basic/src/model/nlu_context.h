#pragma once

#include "../public.h"
#include "fragment/manager_fragment_set.h"

namespace xforce { namespace nlu { namespace basic {

class NluContext {
 public:
  inline explicit NluContext(const std::wstring &query); 

  const std::wstring& GetQuery() const { return query_; }

  inline void SetSegments(const Segment::Set &segments);
  inline void SetChunks(const Chunk::Set &chunks);

  inline const typename Segment::Set& GetSegments() const;
  inline typename Segment::Set& GetSegments();
  inline const typename Chunk::Set& GetChunks() const;
  inline typename Chunk::Set& GetChunks();

 private:
  std::wstring query_;
  ManagerFragmentSet managerFragmentSet_;
};

NluContext::NluContext(const std::wstring &query) :
  query_(query) {}

void NluContext::SetSegments(const typename Segment::Set &segments) {
  segments_ = segments;
}

void NluContext::SetChunks(const typename Chunk::Set &chunks) {
  chunks_ = chunks;
}

const typename Segment::Set& NluContext::GetSegments() const {
  return managerFragmentSet_.GetSegments();
}

typename Segment::Set& NluContext::GetSegments() {
  return managerFragmentSet_.GetSegments();
}

const typename Chunk::Set& NluContext::GetChunks() const {
  return managerFragmentSet_.GetChunks();
}

typename Chunk::Set& NluContext::GetChunks() {
  return managerFragmentSet_.GetChunks();
}

}}}
