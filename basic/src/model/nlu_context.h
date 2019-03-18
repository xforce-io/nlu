#pragma once

#include "../public.h"
#include "segment.h"

namespace xforce { namespace nlu { namespace basic {

class NluContext {
 public:
  inline explicit NluContext(const std::wstring &query); 

  inline void SetSegments(const Segment::Set &segments);

  const std::wstring& GetQuery() const { return query_; }
  const Segment::Set& GetSegments() const { return segments_; }

 private:
  std::wstring query_;
  Segment::Set segments_;
};  

NluContext::NluContext(const std::wstring &query) :
  query_(query) {}

void NluContext::SetSegments(const Segment::Set &segments) {
  segments_ = segments;
}

}}}
