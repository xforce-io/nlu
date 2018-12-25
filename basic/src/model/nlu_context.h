#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace basic {

class NluContext {
 public:
  explicit NluContext(const std::wstring &query); 

  const std::wstring& GetQuery() const { return query_; }
  const Segments& GetSegments() const { return segments_; }

 private:
  std::wstring query_;
  Segments segments_;
};  

NluContext::NluContext(const std::wstring &query) :
  query_(query) {}

}}}
