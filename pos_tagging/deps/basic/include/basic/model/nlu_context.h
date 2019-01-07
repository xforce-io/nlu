#pragma once

#include "../public.h"
#include "segment.h"

namespace xforce { namespace nlu { namespace basic {

class NluContext {
 public:
  inline explicit NluContext(const std::wstring &query); 

  const std::wstring& GetQuery() const { return query_; }
  const Segment::Vector& GetSegments() const { return segments_; }

 private:
  std::wstring query_;
  Segment::Vector segments_;
};  

NluContext::NluContext(const std::wstring &query) :
  query_(query) {}

}}}
