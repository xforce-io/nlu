#pragma once

#include "../public.h"
#include "segment.h"

namespace xforce { namespace nlu { namespace basic {

class NluContext {
 public:
  inline explicit NluContext(const std::wstring &query); 

  inline void SetSegments(const typename Segment::Set &segments);
  inline void SetChunks(const typename Chunk::Set &chunks);

  const std::wstring& GetQuery() const { return query_; }
  const typename Segment::Set& GetSegments() const { return segments_; }
  const typename Chunk::Set& GetChunks() const { return chunks_; }

 private:
  std::wstring query_;
  typename Segment::Set segments_;
  typename Chunk::Set chunks_;
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
